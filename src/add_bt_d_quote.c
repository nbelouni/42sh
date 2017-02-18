/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bt_d_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 00:19:10 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/18 00:19:35 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		create_btq_word(t_word *tmp, t_word **lst, int *i, int len)
{
	t_word	w;
	int		len2;
	int		token;

	token = NO_QUOTE;
	len2 = find_next_nbtq(tmp->s, *i);
	if (len2 < len)
	{
		token = OBT_QUOTE;
		len = len2;
	}
	if (len > 0)
	{
		w = (t_word){ tmp->s + *i, BT_QUOTE, tmp->level, NULL, NULL};
		if (add_new_word(&w, len, lst) < 0)
			return (ERR_EXIT);
		*i += len;
	}
	w = (t_word){ tmp->s, BT_QUOTE, tmp->level + 1, NULL, NULL};
	if (token == OBT_QUOTE && len2 == len)
		return (add_new_btquote(&w, i, lst));
	else
		*i += 1;
	return (0);
}

int		valid_btq(t_word *tmp, int *i, t_word **lst, int start)
{
	int		len;
	int		ret;

	if ((len = find_btquote_end(tmp->s, *i + start)) > 0)
	{
		*i += start;
		if ((ret = create_btq_word(tmp, lst, i, len)) != 0)
			return (ret);
	}
	else
	{
		if (find_btquote_end(tmp->s, *i + start) == 0
		&& (find_btquote_end(tmp->s, *i) == 0))
			*i += start + 1;
		else
			return (tmp->s[*i]);
	}
	if (tmp->flag != NO_QUOTE)
		tmp->level -= 1;
	return (0);
}

int		add_btquote(t_word *tmp, int *i, t_word **lst)
{
	t_word	w;
	int		start;
	int		ret;

	if ((start = is_btquote(tmp->s, *i)) || tmp->flag != NO_QUOTE)
	{
		if ((ret = valid_btq(tmp, i, lst, start)) != 0)
			return (ret);
	}
	w = (t_word){ tmp->s, BT_QUOTE, tmp->level, NULL, NULL};
	if (tmp->flag == OBT_QUOTE)
		return (add_new_btquote(&w, i, lst));
	if (tmp->flag == D_QUOTE)
		return (add_dquote(tmp->s, i, lst, tmp->flag));
	return (add_no_quote(tmp->s, i, lst));
}

int		create_dq_word(char *s, t_word **lst, int *i, int len)
{
	t_word	w;
	int		len2;
	int		token;

	token = NO_QUOTE;
	len2 = find_next_btq(s, *i, &token);
	if (len2 < len)
		len = len2;
	if (len > 0)
	{
		w = (t_word){ s + *i, D_QUOTE, 1, NULL, NULL};
		if (add_new_word(&w, len, lst) < 0)
			return (ERR_EXIT);
		*i += len;
	}
	w = (t_word){ s, D_QUOTE, 2, NULL, NULL};
	if (token == OBT_QUOTE && len2 == len)
		return (add_new_btquote(&w, i, lst));
	else if (token == BT_QUOTE && len2 == len)
		return (add_btquote(&w, i, lst));
	else
		*i += 1;
	return (0);
}

int		add_dquote(char *s, int *i, t_word **lst, int where)
{
	int	start;
	int	len;
	int	ret;

	len = 0;
	if ((start = is_dquote(s, *i)) || where != NO_QUOTE)
	{
		if ((len = find_dquote_end(s, *i + start)) > 0)
		{
			*i += start;
			if ((ret = create_dq_word(s, lst, i, len)) != 0)
				return (ret);
		}
		else
		{
			if (where != NO_QUOTE && find_dquote_end(s, *i) == 0)
				*i += 1;
			else if (find_dquote_end(s, *i + start) == 0
			&& find_dquote_end(s, *i) == 0)
				*i += start + 1;
			else
				return (s[*i]);
		}
	}
	return (add_no_quote(s, i, lst));
}
