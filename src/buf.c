/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:43:38 by alallema          #+#    #+#             */
/*   Updated: 2017/02/05 17:11:56 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_buf		*init_buf(void)
{
	t_buf	*buf;

	if (!(buf = ft_memalloc(sizeof(t_buf))))
		return (NULL);
	if (!(buf->line = ft_memalloc(sizeof(char) * BUFF_SIZE)))
		return (NULL);
	buf->size = 0;
	buf->to_paste = NULL;
	buf->to_paste_size = 0;
	buf->final_line = NULL;
	return (buf);
}

void		free_buf(t_buf *buf)
{
	free(buf->line);
	if (buf->to_paste)
		free(buf->to_paste);
	if (buf->final_line)
		free(buf->final_line);
	free(buf);
	buf = NULL;
}

void		clear_buf(t_buf *buf)
{
	ft_bzero(buf->line, (size_t)(sizeof(char) * BUFF_SIZE));
	buf->size = 0;
}
