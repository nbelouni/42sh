/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:02:12 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/05 16:57:21 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define	OPEN	1
# define	CLOSE	2
# define	DUP		4
# define	WRITE	8

//typedef struct Io	*Io_p;
//typedef struct t_io	*io_p;

typedef struct	s_io
{
	int		flag;
	int		mode;
	int		dup_src;
	int		dup_target;
	int		tab_fd[2];
	char	*str;
}				t_io;

t_io	*new_io();

typedef struct	s_mode
{
	int				redir;
	int				mode;
	int				flag;
}				t_mode;

typedef struct	s_redir
{
	char			*redir;
	int				mode;
}				t_redir;

#endif
