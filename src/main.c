/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/01 20:54:00 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_buf	*buf;

	if (!(buf = init_buf()))
		return (-1);
	while (read_line(buf) >= 0)
	{
		close_termios();
		ft_putstr_fd(buf->line, 1);
		X('\n');
		ft_putnbr_fd(buf->size, 1);
		ft_bzero(buf->line, (size_t)buf->size);
		buf->size = 0;
	}
	close_termios();
	return (0);
}
