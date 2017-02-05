/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:36:00 by alallema          #+#    #+#             */
/*   Updated: 2017/02/05 01:18:45 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

size_t	calc_len(t_buf *buf, int x)
{
	size_t	len;
	size_t	cursor;

	cursor = g_curs.win_col * g_curs.row + g_curs.col;
	len = 0;
	if (x == HOME || x == CTRL_A || x == CTRL_K)
		len = (((g_curs.win_col) * g_curs.row) + g_curs.col - PROMPT_LEN);
	else if (x == END || x == CTRL_F || x == CTRL_W)
		 len = ((buf->size - cursor + PROMPT_LEN) > 0) ? (buf->size - cursor + PROMPT_LEN) : 0;
	else if (x == RIGHT && (cursor - PROMPT_LEN) < (size_t)buf->size)
			return (1);
	else if ((x == LEFT || x == DEL) && (cursor - PROMPT_LEN > 0))
		return (1);
	else if (x == ALT_LEFT || x == CTRL_I || x == CTRL_B)
	{
		while (cursor - len > PROMPT_LEN 
		&& buf->line[cursor - PROMPT_LEN - len - 1] == ' ')
			len++;
		while (cursor - len > PROMPT_LEN 
		&& buf->line[cursor - PROMPT_LEN - len - 1] != ' ')
			len++;
	}
	else if (x == ALT_RIGHT || x == CTRL_N || x == CTRL_E)
	{
		while ((int)(cursor + len) < PROMPT_LEN + buf->size
		&& buf->line[cursor - PROMPT_LEN + len] != ' ')
			len++;
		while ((int)(cursor + len) < PROMPT_LEN + buf->size
		&& buf->line[cursor - PROMPT_LEN + len] == ' ')
			len++;
	}
	return (len);
}

void	m_right(size_t len)
{
	int		cursor;

	PUT2("\nm_right()\n");
	cursor = (g_curs.win_col * g_curs.row) + g_curs.col;
//	E(g_curs.col);X('\n');
	PUT2("cursor : ");E(cursor);
	PUT2(", len : ");E(len);
	PUT2(", cursor + len : ");E(cursor + len);
	PUT2(", col : ");E(g_curs.col);
	PUT2(", row");X(' ');E(g_curs.row);X('\n');
	while (len > 0)
	{
		if (g_curs.col + 1< g_curs.win_col)
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
	PUT2("cursor : ");E(cursor);
	PUT2(", cursor + len : ");E(cursor + len);
	PUT2(", col : ");E(g_curs.col);
	PUT2(", row");X(' ');E(g_curs.row);X('\n');
}

void	m_left(size_t len)
{
	int		cursor;

	PUT2("\nm_left()\n");
	cursor = (g_curs.win_col * g_curs.row) + g_curs.col;
//	E(g_curs.col);X('\n');
	PUT2("cursor : ");E(cursor);
	PUT2(", cursor + len : ");E(cursor + len);
	PUT2(", col : ");E(g_curs.col);
	PUT2(", row");X(' ');E(g_curs.row);X('\n');
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
			tputs(tgoto(tgetstr("ch", NULL), 0, g_curs.win_col - 1), 1, t_putchar);
			g_curs.col = g_curs.win_col - 1;
			g_curs.row--;
		}
		len--;
	}
	cursor = (g_curs.win_col * g_curs.row) + g_curs.col;
	PUT2("cursor : ");E(cursor);
	PUT2(", cursor + len : ");E(cursor + len);
	PUT2(", col : ");E(g_curs.col);
	PUT2(", row");X(' ');E(g_curs.row);X('\n');
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
	if (buf->size - (g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN) > g_curs.win_col)
		m_right(g_curs.win_col);
	else
		m_right(calc_len(buf, END));
}
