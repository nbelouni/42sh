/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 16:49:59 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/15 23:04:29 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
 * on verra pour le return apres
 */
int		add_new_word(char *s, int start, int len, t_word **lst, char *name)
{
	t_word	*new;
	char 	*tmp;

	if (!(tmp = ft_strsub(s, start, len)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(new = create_word()))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	new->s = tmp;
	new->flag = N_QUOTE;
	if (!*lst)
		*lst = new;
	else
		push_word(lst, new);
	PUT2(name);
	PUT2(" : ");
	PUT2(tmp);
	X('\n');
	return (1);
}

int		add_squote(char *s, int *i, t_word **lst)
{
	int	start;
	int	len;

	if ((start = is_squote(s, *i)))
	{
		if ((len = find_squote_end(s, *i + start)))
		{
			if (add_new_word(s, *i + start, len, lst, "squote") < 0)
				return (ERR_EXIT);
			*i = *i + start + len + 1;
		}
		else if (*i + start >= (int)ft_strlen(s) || s[*i + start] != '\'')
			return (s[*i]);
		else
			*i += start + 1;
	}
	return (0);
}

int		add_new_btquote(char *s, int *i, t_word **lst)
{
	int	start;
	int	len;

	if ((start = is_new_btquote(s, *i)))
	{
		if ((len = find_new_btquote_end(s, *i + start)) > 0)
		{
			if (add_new_word(s, *i + start, len, lst, "btquote") < 0)
				return (ERR_EXIT);
			*i = *i + start + len + 1;
		}
		else if (len < 0)
			return (s[*i]);
		else
			*i += start + 1;
	}
	return (0);
}

int		add_btquote(char *s, int *i, t_word **lst)
{
	int	start;
	int	len;
	int	dollar;

	if ((start = is_btquote(s, *i)))
	{
		if ((len = find_btquote_end(s, *i + start)) > 0)
		{
			if ((dollar = find_dollar(s, *i + start)))
			{
				int ret;
				int	tmp_i;
				tmp_i = *i + start + dollar;
				if ((ret = add_new_btquote(s, &tmp_i, lst)))
					return (ret);
				*i = tmp_i;
			}
			if (add_new_word(s, *i + start, len, lst, "btquote") < 0)
				return (ERR_EXIT);
			*i = *i + start + len + 1;
		}
		else if (len < 0)
			return (s[*i]);
		else
			*i += start + 1;
	}
	return (0);
}

int		add_dquote(char *s, int *i, t_word **lst)
{
	int	start;
	int	len;
	int	len2;

	len = 0;
	len2 = 0;
	if ((start = is_dquote(s, *i)))
	{
		*i += start;
		while (*i < (int)ft_strlen(s) && s[*i] != '"')
		{
			len = find_dquote_end(s, *i);
			if (!len)
			{
				if (*i >= (int)ft_strlen(s) || s[*i] != '"')
					return (s[*i - start]);
				else
				{
					*i += 1;
					return (0);
				}
			}
			else if (len > 0)
			{
				if (add_new_word(s, *i, len, lst, "dquote") < 0)
					return (ERR_EXIT);
				*i = *i + len + 1;
				return (0);
			}
			else
			{
				PUT2(s + *i);
				PUT2("___________1\n");
				if ((len2 = add_btquote(s, i, lst)))
					return (len2);
				*i += len2;
				if ((len = find_btquote_end(s, *i)) <= 0)
					len = find_dollar(s, *i);
				if (len > 0 && *i < (int)ft_strlen(s))
				{
					if (add_new_word(s, *i, len, lst, "dquote") < 0)
						return (ERR_EXIT);
					*i += len;
				}
			}
		}
		if (*i >= (int)ft_strlen(s) || s[*i] != '"')
			return (s[*i - start]);
		else
			*i += 1;
	}
	return (0);
}

int		lex_buf(char *s, t_word **lst)
{
	int	i;
	int	tmpi;
	int ret;

	i = 0;
	while (s[i])
	{
		tmpi = i;
		if ((ret = add_squote(s, &i, lst)))
			return (ret);
		else if ((ret = add_btquote(s, &i, lst)))
			return (ret);
		else if ((ret = add_new_btquote(s, &i, lst)))
			return (ret);
		else if ((ret = add_dquote(s, &i, lst)))
			return (ret);
		else if (tmpi == i)
			i++;
	}
	return (0);
}
