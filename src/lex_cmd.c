/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 16:49:59 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/13 23:55:46 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
 * on verra pour le return apres
 */
int		add_new_word(char *s, int start, int len, t_cmd **lst, char *name)
{
	t_cmd	*new;
	char 	*tmp;

	if (!(tmp = ft_strsub(s, start, len)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(new = ft_cmdnew(S_QUOTE, tmp)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!*lst)
		*lst = new;
	else
		ft_cmdpush(lst, new);
	PUT1(name);
	PUT1(" : ");
	PUT1(tmp);
	X('\n');
	return (1);
}

int		lex_buf(t_buf *buf, t_cmd **lst)
{
	int	i;
	int	start;
	int	len;
	char	*s;

	s = buf->final_line;

	i = 0;
	while (s[i])
	{
		len = 0;
		if ((start = is_squote(s, i)))
		{
			if ((len = find_squote_end(s, i + start)))
			{
				if (add_new_word(s, i + start, len, lst, "squote") < 0)
					return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
				i = i + start + len + 1;
			}
			else
				return (s[i]);
		}
		else if ((start = is_btquote(s, i)))
		{
			if ((len = find_btquote_end(s, i + start, s[i])))
			{
				if (add_new_word(s, i + start, len, lst, "btquote") < 0)
					return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
				i = i + start + len + 1;
			}
			else
				return (s[i]);
		}
		else if ((start = is_dquote(s, i)))
		{
			if (s[i + start] == '"')
				i++;
			else
			{
				while (i + start + len < (int)ft_strlen(s) && s[i + start] != '"')
				{
						PUT1("________-1\n");
					len = find_dquote_end(s, i + start);
					if (!len)
					{
						PUT1("________0\n");
						return (s[i]);
					}
					if (len > 0)
					{
						PUT1("________1\n");
						if (add_new_word(s, i + start, len, lst, "dquote") < 0)
							return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
						i = i + start + len + 1;
						break ;
					}
					else
					{
						PUT1("________2\n");
						len = 0;
						while (!is_btquote(s, i + len))
							len++;
						len--;
						if (add_new_word(s, i + start, len, lst, "dquote") < 0)
							return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
						start += len + 1;
						PUT1("s + start : ");
						PUT1(s + start);
						X('\n');
						if ((len = find_btquote_end(s, i + start, s[i + start - 1])))
						{
							if (add_new_word(s, i + start, len, lst, "btquote") < 0)
								return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
						PUT1("________3\n");
							i = i + start + len + 1;
						}
						else
							return (s[i]);
					}
				}
				if (i + start + len >= (int)ft_strlen(s))
					return (s[i]);
			}
		}
		else
			i++;
	}
	return (0);
}
