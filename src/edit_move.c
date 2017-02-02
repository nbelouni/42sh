/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:36:00 by alallema          #+#    #+#             */
/*   Updated: 2017/02/02 22:30:26 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	m_right(t_buf *buf)
{
	E(buf->size);X(' ');
	E(g_curs->col);X(' ');
	E(g_curs->row);X(' ');
	E(g_curs->win_col);X(' ');
	E(g_curs->win_row);X('\n');X('\n');
	if (buf->size > (g_curs->win_col * g_curs->row) + g_curs->col + PROMPT_LEN) // a refaire pour le multiligne
	{
		t_puts("nd", 1);
		if (g_curs->col < g_curs->win_col)
			g_curs->col++;
		else
		{
			g_curs->col = 0;
			g_curs->row++;
		}
	}
	E(buf->size);X(' ');
	E(g_curs->col);X(' ');
	E(g_curs->row);X(' ');
	E(g_curs->win_col);X(' ');
	E(g_curs->win_row);X('\n');X('\n');
}

void	m_left(t_buf *buf)
{
	E(buf->size);X(' ');
	E(g_curs->col);X(' ');
	E(g_curs->row);X(' ');
	E(g_curs->win_col);X(' ');
	E(g_curs->win_row);X('\n');
	(void)buf;
	if ((g_curs->win_col * g_curs->row) + g_curs->col > PROMPT_LEN) // a refaire pour le multiligne
	{
		t_puts("le", 1);
		if (g_curs->col > 0)
			g_curs->col--;
		else if (g_curs->row > 0)
		{
			g_curs->col = g_curs->win_col;
			g_curs->row--;
		}
	}
	E(buf->size);X(' ');
	E(g_curs->col);X(' ');
	E(g_curs->row);X(' ');
	E(g_curs->win_col);X(' ');
	E(g_curs->win_row);X('\n');X('\n');
}

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
	;
	(void)buf;
}

void	m_ctrl_r(t_buf *buf)
{
	;
	(void)buf;
}

void	m_ctrl_l(t_buf *buf)
{
	(void)buf;
}


