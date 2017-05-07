/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:15:27 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/07 18:29:10 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# include <fcntl.h>

typedef struct	s_str
{
	int			i;
	int			j;
	int			read;
	int			fd;
	char		*s;
}				t_str;

int				get_next_line(int const fd, char **line);

#endif
