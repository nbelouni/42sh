/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:05:19 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/04 16:24:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "read.h"
#include <errno.h>

extern t_bool	g_is_here_doc;

int			cpy_cut_paste(t_buf *buf, int x)
{
	if (x == CTRL_F || x == CTRL_N || x == CTRL_A || x == CTRL_L)
	{
		if (vb_copy(buf, x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
		}
	}
	if (x == CTRL_B || x == CTRL_E || x == CTRL_K || x == CTRL_W)
	{
		if (vb_cut(buf, x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
		}
	}
	if (buf->size + buf->to_paste_size < BUFF_SIZE && x == CTRL_P)
	{
		if (vb_paste(buf) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
	}
	return (0);
}

int			read_modul(int x, t_buf *buf)
{
	if (buf->size + 1 < BUFF_SIZE && (x > 31 && x < 127))
	{
		if (vb_insert(buf, (char *)&x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
		return (1);
	}
	return (0);
}

int			mv_and_read(t_buf *buf, int x, int ret)
{
	if (ret < 0)
		return (ft_print_error("\n21sh", ERR_READ, ERR_EXIT));
	if (x == CTRL_D)
		return (CTRL_D);
	if (x == DEL)
		vb_del(buf, x);
	if (x == ALT_UP)
		m_up();
	if (x == ALT_DOWN)
		m_down(buf);
	if (x == LEFT || x == HOME || x == ALT_LEFT)
		m_left(calc_len(buf, x));
	if (x == RIGHT || x == END || x == ALT_RIGHT)
		m_right(calc_len(buf, x));
	return (0);
}

static int	check_ret(int *tabi, t_completion *cplt, t_lst *hist, t_buf *buf)
{
	if ((tabi[2] = mv_and_read(buf, tabi[0], tabi[1])) != 0 ||
		(tabi[2] = cpy_cut_paste(buf, tabi[0])) != 0 ||
		((tabi[2] = complete_line(buf, cplt, tabi[0])) != 0) ||
		(tabi[2] = edit_history(buf, hist, tabi[0]) != 0))
	{
		return (tabi[2]);
	}
	else if (tabi[0] == RETR)
	{
		m_right(calc_len(buf, END));
		ft_putchar_fd((char)tabi[0], 1);
		ft_strdel(&(buf->last_cmd));
		buf->cur_hist = NULL;
		return (0);
	}
	else
		return (2);
}
/*
**  integre les copier coller a la souris
*/

int			read_line(t_buf *buf, t_completion *cplt, t_lst *hist)
{
	int	tabi[3];
	int	ret;

	tabi[0] = 0;
	tabi[1] = 0;
	tabi[2] = 0;
	ret = 0;
	init_line(buf);
	while ((tabi[1] = read(0, &tabi[0], sizeof(int))))
	{
		if (tabi[1] < 0 && errno == EINTR)
			return (ERR_NEW_CMD);
		if (classic_read(buf, tabi[0]) == 1)
		{
			ret = check_ret(tabi, cplt, hist, buf);
			if (ret == TAB || ret < 1)
				return (ret);
			if (ret == CTRL_D && buf->size == 0 && ((g_is_here_doc == FALSE
			&& !ft_strlen(buf->final_line)) || g_is_here_doc == TRUE))
				return (g_is_here_doc == TRUE ? CTRL_D : ERR_EXIT);
		}
		tabi[0] = 0;
	}
	close_termios();
	return (END_EOT);
}
