/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:36:00 by alallema          #+#    #+#             */
/*   Updated: 2017/02/03 22:16:49 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

size_t	calc_len(t_buf *buf, int x)
{
	size_t	len;

	len = 0;
	if (x == HOME || x == CTRL_W /*copy*/)
		return ((((g_curs.win_col + 1)* g_curs.row) + g_curs.col - PROMPT_LEN));
	if (x == END || x == CTRL_L || x == RETR/*|| [PAST_AFT]*/)
		return ((buf->size - (g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN)));
	if (x == RIGHT && (g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN)
		<= buf->size)
			return (1);
	else if ((x == LEFT || x == DEL) && (g_curs.win_col * g_curs.row + g_curs.col
		- PROMPT_LEN > 0))
		return (1);
	else
		return (0);
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
//	E(len);X(' ');
	E(g_curs.col);X(' ');
	E(g_curs.win_col);X(' ');
	E(g_curs.row);X('\n');
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
	E(g_curs.col);X(' ');
	E(g_curs.win_col);X(' ');
	E(g_curs.row);X('\n');X('\n');
}

void	ft_del(size_t len)
{
	while (len > 0)
	{
		m_left(1);
		t_puts("dm", 1);
		t_puts("dc", 1);
		t_puts("ed", 1);
		len--;
	}
}

void	m_left(size_t len)
{
	E(len);X(' ');
	E(g_curs.col);X(' ');
	E(g_curs.win_col);X(' ');
	E(g_curs.row);X('\n');
	while (len > 0)
	{
		t_puts("le", 1);
		if (g_curs.col > 0 || (g_curs.row == 0 && g_curs.col > PROMPT_LEN))
			g_curs.col--;
		else if (g_curs.row > 0)
		{
			g_curs.col = g_curs.win_col;
			g_curs.row--;
		}
		len--;
	}
//	E(len);X(' ');
	E(g_curs.col);X(' ');
	E(g_curs.win_col);X(' ');
	E(g_curs.row);X('\n');X('\n');

//	E(buf->size);X(' ');
//	E(g_curs.col);X(' ');
//	E(g_curs.row);X(' ');
//	E(g_curs.win_col);X(' ');
//	E(g_curs.win_row);X('\n');X('\n');
}
/*
void	m_up(t_buf *buf)
{
	(void)buf;
}

void	m_down(t_buf *buf)
{
	;
	(void)buf;
}

void	m_end(t_buf *buf)
{
	;
	(void)buf;
}

void	m_home(t_buf *buf)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, PROMPT_LEN), 1, t_putchar);
//	t_puts("cr", 4);
	(void)buf;
	g_curs.col = 0;
	g_curs.row = 0;
}

void	m_ctrl_r(t_buf *buf)
{
	;
	(void)buf;
}

void	m_ctrl_l(t_buf *buf)
{
	(void)buf;
}*/
