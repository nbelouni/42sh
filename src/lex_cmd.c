/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 17:33:42 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/24 19:41:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		add_new_word(t_word *w, int len, t_word **lst)
{
	t_word	*new;
	char	*tmp;

	if (!(tmp = ft_strsub(w->s, 0, len)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(new = create_word()))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	new->s = tmp;
	new->level = w->level;
	new->flag = w->flag;
	if (!*lst)
		*lst = new;
	else
		push_word(lst, new);
	return (1);
}

int		add_squote(char *s, int *i, t_word **lst)
{
	int		start;
	int		len;
	t_word	w;

	if (!s || *i >= (int)ft_strlen(s))
		return (0);
	if ((start = is_squote(s, *i)))
	{
		if ((len = find_squote_end(s, *i + start)))
		{
			w = (t_word){ s + *i + start, S_QUOTE, 1, NULL, NULL};
			if (add_new_word(&w, len, lst) < 0)
				return (ERR_EXIT);
			*i = *i + start + len + 1;
		}
		else if (*i + start >= (int)ft_strlen(s) || s[*i + start] != '\'')
			return (s[*i]);
		else
			*i += start + 1;
	}
	return (add_no_quote(s, i, lst));
}

int		add_no_quote(char *s, int *i, t_word **lst)
{
	t_word	w;
	int		len;
	int		token;

	token = 0;
	if (!s || *i >= (int)ft_strlen(s))
		return (0);
	len = find_next_inhibitor(s, *i, &token);
	if (len > 0)
	{
		w = (t_word){ s + *i, NO_QUOTE, 0, NULL, NULL};
		if (add_new_word(&w, len, lst) < 0)
			return (ERR_EXIT);
		*i = *i + len;
	}
	w = (t_word){ s, NO_QUOTE, 1, NULL, NULL};
	if (token == S_QUOTE)
		return (add_squote(s, i, lst));
	if (token == D_QUOTE)
		return (add_dquote(s, i, lst, NO_QUOTE));
	if (token == BT_QUOTE)
		return (add_btquote(&w, i, lst));
	if (token == OBT_QUOTE)
		return (add_new_btquote(&w, i, lst));
	return (0);
}

int		lex_buf(char *s, t_word **lst)
{
	int	i;
	int ret;

	i = 0;
	if (!s || !s[i])
		return (0);
	ret = add_no_quote(s, &i, lst);
	if (ret == ERR_EXIT)
	{
		destroy_word(lst);
		return (ERR_EXIT);
	}
	else if (ret)
	{
		destroy_word(lst);
		return (ERR_NEW_PROMPT);
	}
	return (0);
}
