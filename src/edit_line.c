/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:28:17 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/04 00:08:58 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"


void		vb_insert(t_buf *buf, char *s)
{
	t_puts("im", 1);
	t_puts("ic", 1);
	ft_putchar_fd(*s, 1);
	insert_in_buf(buf, g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN, s, 1);
	buf->size++;
	if (g_curs.col < g_curs.win_col)
		g_curs.col += 1;
	else
	{
		g_curs.col = 0;
		g_curs.row++;
		t_puts("cr", 1);
		t_puts("do", 1);
		X('*');
	}
//	E(g_curs.col);X(' ');
//	E(g_curs.win_col);X(' ');
//	E(g_curs.row);X('\n');
	t_puts("ei", 1);
	print_post_curs(buf);
}

void		vb_del(t_buf *buf, unsigned int x)
{
	int		len;
   
	len = calc_len(buf, x);
	delete_in_buf(buf, g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN, len);
	tab_move[2](len);
	buf->size = ft_strlen(buf->line);
	print_post_curs(buf);
}
