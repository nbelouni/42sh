/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:03:10 by alallema          #+#    #+#             */
/*   Updated: 2017/02/02 22:41:30 by alallema         ###   ########.fr       */
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
	while ((ret = read(0, (char *)&x, 4)))
	{
		E(x);X(' ');
		if (ret < 0 || buf->size > BUFF_SIZE)
			return (-1);
		if (x == CTRL_D)
			return (-2);
		if (x > 31 && x < 127)
		{
			t_puts("im", 1);
			t_puts("ic", 1);
			ft_putchar_fd((char)x, 2);
			ft_putchar_fd((char)x, 1);
			buf->line[g_curs->win_col * g_curs->row + g_curs->col] = (char)x;
			buf->size++;
			if (g_curs->col < g_curs->win_col)
				g_curs->col++;
			else
			{
				g_curs->col = 0;
				g_curs->row++;
			}
		}
		if (x == LEFT)
			tab_move[1](buf);
		if (x == RIGHT)
			tab_move[0](buf);
		if (x == RETR)
		{
			ft_putchar_fd((char)x, 1);
			return (0);
		}
		x = 0;
	}
	return (0);
}
