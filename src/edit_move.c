/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:36:00 by alallema          #+#    #+#             */
/*   Updated: 2017/02/05 16:44:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	m_right(size_t len)
{
	int		cursor;

	cursor = (g_curs.win_col * g_curs.row) + g_curs.col;
	while (len > 0)
	{
		if (g_curs.col + 1 < g_curs.win_col)
		{
			t_puts("nd", 1);
			g_curs.col++;
		}
		else
		{
			t_puts("cr", 1);
			t_puts("do", 1);
			g_curs.col = 0;
			g_curs.row++;
		}
		len--;
	}
	cursor = (g_curs.win_col * g_curs.row) + g_curs.col;
}

void	m_left(size_t len)
{
	int		cursor;
	int		w_col;

	w_col = g_curs.win_col;
	cursor = (w_col * g_curs.row) + g_curs.col;
	while (len > 0)
	{
		if (g_curs.col > 0
		|| (g_curs.row == 0 && g_curs.col > (int)get_prompt_len()))
		{
			t_puts("le", 1);
			g_curs.col--;
		}
		else if (g_curs.row > 0)
		{
			t_puts("up", 1);
			tputs(tgoto(tgetstr("ch", NULL), 0, w_col - 1), 1, t_putchar);
			g_curs.col = w_col - 1;
			g_curs.row--;
		}
		len--;
	}
}

void	m_up(void)
{
	if (g_curs.row > 0)
	{
		t_puts("up", 1);
		g_curs.row--;
	}
}

void	m_down(t_buf *buf)
{
	size_t	cursor;

	cursor = g_curs.win_col * g_curs.row + g_curs.col;
	if (buf->size - (cursor - get_prompt_len()) > (size_t)g_curs.win_col)
		m_right(g_curs.win_col);
	else
		m_right(calc_len(buf, END));
}
