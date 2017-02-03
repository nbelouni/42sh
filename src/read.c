/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:03:10 by alallema          #+#    #+#             */
/*   Updated: 2017/02/03 22:16:50 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "read.h"

int		read_line(t_buf *buf)
{
	unsigned int	x;
	int				ret;

	x = 0;
	init_termios();
	ft_putstr_fd("42sh>", 1);
	while ((ret = read(0, (char *)&x, 4)))
	{
		if (ret < 0)
			return (-1);
		if (buf->size > BUFF_SIZE)
			return (0);
		if (x == CTRL_D)
			return (-2);
		if (x > 31 && x < 127)
		{
			t_puts("im", 1);
			t_puts("ic", 1);
			ft_putchar_fd((char)x, 1);
			insert_in_buf(buf, g_curs.win_col * g_curs.row + g_curs.col - PROMPT_LEN, (char *)&x, 1);
			buf->size++;
			if (g_curs.col < g_curs.win_col)
				g_curs.col += 1;
			else
			{
				g_curs.col = 0;
				g_curs.row++;
			}
			E(g_curs.col);X(' ');
			E(g_curs.win_col);X(' ');
			E(g_curs.row);X('\n');
			t_puts("ei", 1);
		}
//		if (x == HOME)
//			m_home(buf);
		if (x == DEL)
			tab_move[2](calc_len(buf, x));
		if (x == LEFT || x == HOME)
			tab_move[1](calc_len(buf, x));
		if (x == RIGHT || x == END)
			tab_move[0](calc_len(buf, x));
		if (x == RETR)
		{
			tab_move[0](calc_len(buf, x));
			ft_putchar_fd((char)x, 1);
			return (0);
		}
		x = 0;
	}
	close_termios();
	return (0);
}
