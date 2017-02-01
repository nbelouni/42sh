/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:03:10 by alallema          #+#    #+#             */
/*   Updated: 2017/02/01 21:03:00 by alallema         ###   ########.fr       */
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
		if (ret < 0 || buf->size > BUFF_SIZE)
			return (-1);
		if (x == CTRL_D)
			return (-2);
		if (x > 31 && x < 127)
		{
			ft_putchar_fd((char)x, 1);
			buf->line[buf->size] = (char)x;
			buf->size++;
		}
		if (x == RETR)
		{
			ft_putchar_fd((char)x, 1);
			return (0);
		}
	}
	return (0);
}
