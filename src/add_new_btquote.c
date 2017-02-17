/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_btquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 23:18:36 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/18 00:03:17 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		add_new_btquote(t_word *tmp, int *i, t_word **lst)
{
//	int	start;
//	int	len;
//	int	len2;
//	int	token;	
	(void)tmp;
	(void)i;
	(void)lst;

	return (ft_print_error("42sh: ", "`$()' : Not implemented <3", 48));
	/*
	token = NO_QUOTE;
	if (!s || *i >= (int)ft_strlen(s))
		return (0);
	if ((start = is_new_btquote(s, *i)) || where != NO_QUOTE)
	{
		if ((len = find_new_btquote_end(s, *i + start)) > 0)
		{
			*i += start;
			len2 = find_next_btq(s, *i, &token);
			if (len2 < len)
				len = len2;	
			if (len > 0)
			{
				if (add_new_word(s + *i, len, lst, OBT_QUOTE, level) < 0)
					return (ERR_EXIT);
				*i += len;
			}
			if (token == BT_QUOTE && len2 == len)
				return (add_btquote(s, i, lst, OBT_QUOTE, level + 1));
			else if (token == OBT_QUOTE && len2 == len)
				return (add_new_btquote(s, i, lst, OBT_QUOTE, level + 1));
			else
			{
				*i += 1;
			}
		}
		else
		{
			PUT2(s + *i);
			X(' ');
			E(where);
			X(' ');
			E(find_new_btquote_end(s, *i + start));
			X(' ');
			E(find_new_btquote_end(s, *i));
			X('\n');
			if (find_new_btquote_end(s, *i + start) == 0
			&& find_new_btquote_end(s, *i) == start)
			{
				*i += start + 1;
			}
			else if (where != NO_QUOTE && find_new_btquote_end(s, *i) == 0)
			{
				*i += 1;
			}
			else
			{
				return (s[*i]);
			}
		}
		if (where != NO_QUOTE)
			level -= 1;
	}

			E(level);
			X('\n');
	if (where == BT_QUOTE && level > 0)
		return (add_btquote(s, i, lst, where, level));
	else if (where == OBT_QUOTE && level > 0)
		return (add_new_btquote(s, i, lst, where, level));
	else if (where == D_QUOTE && level > 0)
		return (add_dquote(s, i, lst, OBT_QUOTE));
	return (add_no_quote(s, i, lst));
	*/
}

