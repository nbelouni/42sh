/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:02:12 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/24 18:59:14 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define	OPEN	1
# define	CLOSE	2
# define	DUP		4
# define	WRITE	8

//(x == DIR_AMP || x == SR_DIR || x == SL_DIR || x == DR_DIR || x == DL_DIR)

typedef struct Io	*Io_p;
/*
enum	IoType
{
	IO_PIPE,
	IO_SR,
	
};
*/
struct	Io
{
	int		flag;
	int		dup_src;
	int		dup_target;
	int		mode;
	char	*str;
};

Io_p new_io();

#endif
