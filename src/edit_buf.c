/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 23:40:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/03 22:52:45 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		insert_in_buf(t_buf *buf, int cursor, char *s, size_t len)
{
	char	tmp[buf->size - cursor + 1];

	if (buf->size + len >= BUFF_SIZE)
		return ;
	if (cursor < buf->size - 1)
	{
		ft_strncpy(tmp, buf->line + cursor, buf->size - cursor + 1);
		tmp[buf->size - cursor] = 0;
		ft_strncpy(buf->line + cursor, s, len);
		ft_strncpy(buf->line + cursor + len, tmp, buf->size - cursor);
	}
	else
	{
		ft_strncpy(buf->line + buf->size, s, len);
		buf->line[buf->size + len] = 0;
	}
}

void		delete_in_buf(t_buf *buf, int cursor, size_t len)
{
	char	tmp[buf->size];

	ft_bzero(tmp, buf->size);
	if (len == 0)
		return ;
	if (cursor >= buf->size)
		ft_bzero(buf->line + buf->size - len, len);
	else
	{
		ft_strncpy(tmp, buf->line + cursor, buf->size - cursor);
		ft_strncpy(buf->line + cursor - len, tmp, buf->size - cursor);
		ft_bzero(buf->line + buf->size - len, len);
	}
}
