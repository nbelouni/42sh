/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:02:14 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/28 14:32:46 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "42sh.h"
#include "io.h"

Io_p new_io(int flag, int mode)
{
	Io_p	io;

	io = malloc(sizeof(struct Io));
	bzero(io, sizeof(struct Io));
	io->flag = flag;
	io->mode = mode;
	return(io);
}

