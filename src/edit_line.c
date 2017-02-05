/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 22:28:17 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/05 00:58:54 by nbelouni         ###   ########.fr       */
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
	if (g_curs.col + 1 < g_curs.win_col)
		g_curs.col += 1;
	else
	{
		g_curs.col = 0;
		g_curs.row++;
		t_puts("cr", 1);
		t_puts("do", 1);
	}
	print_post_curs(buf);
	t_puts("ei", 1);
}

void		vb_del(t_buf *buf, unsigned int x)
{
	int len;
	int	cursor;

	len = calc_len(buf, x);
	if (x == CTRL_E || x == CTRL_W)
		cursor = g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN + len;
	else
		cursor = g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN;
	if (cursor < 0)
		cursor = 0;
	if (cursor > buf->size)
		cursor = buf->size - 1;
	delete_in_buf(buf, cursor, len);
	if (x != CTRL_E && x != CTRL_W)
		m_left(len);
	buf->size = ft_strlen(buf->line);
	print_post_curs(buf);
}

int			vb_copy(t_buf *buf, unsigned int x)
{
	int len;
	int	cursor;

	len = calc_len(buf, x);
	if (x == CTRL_E || x == CTRL_W || x == CTRL_N ||x == CTRL_F)
		cursor = g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN;
	else
		cursor = g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN - len;
	if (cursor < 0)
		cursor = 0;
	if (cursor > buf->size)
		cursor = buf->size - 1;
	if (set_to_paste(buf, cursor, len) < 0)
		return (-1);
	return (0);
}

int			vb_cut(t_buf *buf, unsigned int x)
{
	if (vb_copy(buf, x) < 0)
		return (-1);
	vb_del(buf, x);
	return (0);
}

void		vb_paste(t_buf *buf)
{
	if (!buf->to_paste)
		return ;
	paste_in_buf(buf, g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN);
	buf->size += buf->to_paste_size;
	print_post_curs(buf);
}
