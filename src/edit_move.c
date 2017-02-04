/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:36:00 by alallema          #+#    #+#             */
/*   Updated: 2017/02/04 01:48:33 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

size_t	calc_len(t_buf *buf, int x)
{
	size_t	len;

	len = 0;
	if (x == HOME || x == CTRL_W /*copy*/)
		len = (((g_curs.win_col + 1) * g_curs.row) + g_curs.col - PROMPT_LEN);
	if (x == END || x == CTRL_L || x == RETR/*|| [PAST_AFT]*/)
		len = (buf->size - (g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN));
	if (x == RIGHT && (g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN)
		< buf->size)
			return (1);
	if ((x == LEFT || x == DEL) && (g_curs.win_col * g_curs.row + g_curs.col
		- PROMPT_LEN > 0))
		return (1);
	if (x == CTRL_L)
	{
		while (buf->line[g_curs.col + len] != ' ')
			len++;
	}
	if (x == CTRL_L)
	{
		while ((int)len < g_curs.col && buf->line[g_curs.col - len] != ' ')
			len++;
	}
	return (len);
}

void	m_right(size_t len)
{
	while (len > 0)
	{
		if (g_curs.col < g_curs.win_col)
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
}

void	m_left(size_t len)
{
	E(g_curs.col);X('\n');
	while (len > 0)
	{
		if (g_curs.col > 0 || (g_curs.row == 0 && g_curs.col > PROMPT_LEN))
		{
			t_puts("le", 1);
			g_curs.col--;
		}
		else if (g_curs.row > 0)
		{
			t_puts("up", 1);
			tputs(tgoto(tgetstr("ch", NULL), 0, g_curs.win_col + 1), 1, t_putchar);
			g_curs.col = g_curs.win_col;
			g_curs.row--;
		}
		len--;
	}
	E(g_curs.col);X('\n');
}
/*
void	m_home(t_buf *buf)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, PROMPT_LEN), 1, t_putchar);
//	t_puts("cr", 4);
	(void)buf;
	g_curs.col = 0;
	g_curs.row = 0;
}
*/
