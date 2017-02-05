/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:03:10 by alallema          #+#    #+#             */
/*   Updated: 2017/02/05 14:42:52 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "read.h"

int		cpy_cut_paste(t_buf *buf, int x)
{
	if (x == CTRL_F || x == CTRL_N || x == CTRL_A || x == CTRL_I)
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
	if (x == CTRL_P)
	{
		if (vb_paste(buf) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
	}
	return (0);
}

int		mv_and_read(t_buf *buf, int x, int ret)
{
	if (ret < 0)
		return (ft_print_error("\n42sh", ERR_READ, ERR_EXIT));
	if (x == CTRL_D)
		return (ERR_EXIT);
	if (x > 31 && x < 127)
	{
		if (vb_insert(buf, (char *)&x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
	}
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

int		read_line(t_buf *buf)
{
	unsigned int	x;
	int				ret;
	int				err;

	x = 0;
	err = 0;
	init_termios();
	ft_putstr_fd("42sh.$ ", 1);
	while ((ret = read(0, (char *)&x, 4)))
	{
		if ((err = mv_and_read(buf, x, ret)) < 0)
			return (err);
		if ((err = cpy_cut_paste(buf, x)) < 0)
			return (err);
		if (x == RETR)
		{
			m_right(calc_len(buf, END));
			ft_putchar_fd((char)x, 1);
			return (0);
		}
		x = 0;
	}
	return (0);
}
