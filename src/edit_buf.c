/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 23:40:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/03 23:54:40 by nbelouni         ###   ########.fr       */
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

void		set_to_past(t_buf *buf, int cursor, size_t len)
{
	if (buf->to_paste != NULL)
		free(buf->to_paste);
	buf->to_paste = ft_strsub(buf->line, cursor, len);
	buf->to_paste_size = len;
}

void		paste_in_buf(t_buf *buf, int cursor)
{
	char	tmp[buf->size - cursor + 1];

	if (buf->size + buf->to_paste_size >= BUFF_SIZE)
		return ;
	if (cursor < buf->size - 1)
	{
		ft_strncpy(tmp, buf->line + cursor, buf->size - cursor + 1);
		tmp[buf->size - cursor] = 0;
		ft_strncpy(buf->line + cursor, buf->to_paste, buf->to_paste_size);
		ft_strncpy(buf->line + cursor + buf->to_paste_size, tmp, buf->size - cursor);
	}
	else
	{
		ft_strncpy(buf->line + buf->size, buf->to_paste, buf->to_paste_size);
		buf->line[buf->size + buf->to_paste_size] = 0;
	}
}
