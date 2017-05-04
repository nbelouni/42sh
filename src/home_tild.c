/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_tild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:06:10 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:22:52 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_core	*g_core;

void	tild_per_home(t_elem *home, t_buf *buf, int len)
{
	char	*tmp;

	vb_del(buf, DEL);
	tmp = buf->to_paste;
	buf->to_paste = ft_strdup(home->value);
	buf->to_paste_size = ft_strlen(buf->to_paste);
	vb_paste(buf);
	m_right(len + buf->to_paste_size);
	ft_strdel(&(buf->to_paste));
	buf->to_paste = tmp;
	buf->to_paste_size = ft_strlen(tmp);
}

void	home_tild(t_buf *buf, int *begin)
{
	int		len;
	int		c_pos;
	t_elem	*home;

	home = ft_find_elem("HOME", g_core->env);
	if (home && home->value)
	{
		len = 0;
		c_pos = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len();
		while (c_pos > 0 && buf->line[c_pos - 1] != '~')
		{
			len += 1;
			m_left(1);
			c_pos -= 1;
		}
		if (buf->line[c_pos] != '/')
		{
			m_right(len);
			return ;
		}
		tild_per_home(home, buf, len);
		*begin = find_word_begin(buf->line, c_pos);
	}
}
