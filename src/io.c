/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:02:14 by llaffile          #+#    #+#             */
/*   Updated: 2017/05/04 17:05:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

t_io	*new_io(int flag, int mode)
{
	t_io	*io;

	if (!(io = ft_memalloc(sizeof(t_io))))
		return (NULL);
	ft_bzero(io, sizeof(t_io));
	io->flag = flag;
	io->mode = mode;
	io->tab_fd[0] = -1;
	io->tab_fd[1] = -1;
	io->tab_fd[2] = -1;
	return (io);
}
