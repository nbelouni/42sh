/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:47:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/20 15:56:51 by maissa-b         ###   ########.fr       */
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

int 	read_modul(int x, t_buf *buf)
{
	if ((x > 31 && x < 127))
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

int		mv_and_read(t_buf *buf, int x, int ret)
{
	if (ret < 0)
		return (ft_print_error("\n42sh", ERR_READ, ERR_EXIT));
	if (x == CTRL_D)
		return (ERR_EXIT);
	//if (read_modul(x, buf) == 1)
		//return (1);
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

/*
**	Y faut trouver un autre moyen de recuperer les caracteres speciaux
*/

void	init_line(t_buf *buf)
{
	init_termios();
	ft_putstr_fd(get_prompt_str(), 1);
	print_pre_curs(buf);
	print_post_curs(buf);
}
/*
**  integre les copier coller a la souris
*/

int		classic_read(t_buf *buf, int x)
{
  int tmp;

  	tmp = x & 0xff;
 	if (tmp < 31 || tmp > 127)
 		return (1);
 	while (x)
 	{
 		tmp = x & 0xff;
 		x >>= 8;
 		read_modul(tmp, buf);
 	}
	return (1);
}

int		read_line(t_buf *buf, t_completion *cplt, t_lst *hist)
{
	unsigned int	x;
	int				ret;
	int				err;
	int				i;

	i = -1;
	x = 0;
	err = 0;
	init_line(buf);
	while ((ret = read(0, &x, sizeof(int))))
	{
		 if (classic_read(buf, x) == 1)
		 {
			if ((err = mv_and_read(buf, x, ret)) < 0 ||
			(err = cpy_cut_paste(buf, x)) < 0 ||
			(err = complete_line(buf, cplt, x)) != 0 ||
			(err = edit_history(buf, hist, x) != 0))
			return (err);
			if (x == RETR)
			{
				m_right(calc_len(buf, END));
				ft_putchar_fd((char)x, 1);
				ft_strdel(&(buf->last_cmd));
				buf->cur_hist = NULL;
				return (0);
			 }
		 }
		x = 0;
	}
	close_termios();
	return (END_EOT);
}
