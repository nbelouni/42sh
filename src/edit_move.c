/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 21:36:00 by alallema          #+#    #+#             */
/*   Updated: 2017/02/03 18:10:12 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** return valeur de len;
** [HOME]  && [CUT_BEF] && [PAST_BEF] = ((g_curs.win_col * g_curs.row) + g_curs.col);
** [END] && [CUT_AFT] && [PAST_AFT] = (buf->size - (g_curs.win_col * g_curs.win_row + g_curs.col));
** [LEFT] && [RIGHT] = 1;
** [WRD_BEF] = while (buf->size != ' ');
** [WRD_AFT] = while (buf->size != ' ');
*/

size_t	calc_len(t_buf *buf, int x)
{
	size_t	len;

	len = 0;
	if (x == HOME || x == CTRL_W /*copy*/)
		return (((g_curs.win_col * g_curs.row) + g_curs.col));
	if (x == END || x == CTRL_L || x == RETR/*|| [PAST_AFT]*/)
		return ((buf->size - (g_curs.win_col * g_curs.row + g_curs.col)));
	if (x == LEFT || x == RIGHT)
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
			ft_putstr_fd("_________2\n", 2);
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
	while (len > 0)
	{
		t_puts("le", 1);
		if (g_curs.col > 0)
			g_curs.col--;
		else if (g_curs.row > 0)
		{
				ft_putstr_fd("_________3\n", 2);
			g_curs.col = g_curs.win_col - 1;
			g_curs.row--;
		}
		len--;
	}
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
