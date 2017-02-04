/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:03:10 by alallema          #+#    #+#             */
/*   Updated: 2017/02/04 00:30:35 by nbelouni         ###   ########.fr       */
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
	ft_putstr_fd("42sh.$ ", 1);
	while ((ret = read(0, (char *)&x, 4)))
	{
		if (ret < 0)
			return (-1);
		if (buf->size > BUFF_SIZE)
			return (0);
		if (x == CTRL_D)
			return (-2);
		if (x > 31 && x < 127)
			vb_insert(buf, (char *)&x);
		if (x == DEL)
			vb_del(buf, x);
		if (x == LEFT || x == HOME || x == ALT_LEFT)
			tab_move[1](calc_len(buf, x));
		if (x == RIGHT || x == END || x == ALT_RIGHT)
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
