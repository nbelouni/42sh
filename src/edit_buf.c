/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 23:40:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/03 00:44:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		insert_c(t_buf *buf, int cursor, char c)
{
	char	tmp[buf->size - cursor];

	if (cursor < buf->size - 1)
	{
		ft_memcpy(tmp, buf->line + cursor, buf->size - cursor);
		buf->line[cursor] = c;
		ft_memcpy(buf->line + cursor, tmp, buf->size - cursor);
	}
	else
		buf->line[cursor] = c;
}

void		delete_c(t_buf *buf, int cursor)
{
	char	tmp[buf->size - cursor];

	if (cursor < buf->size - 1)
	{
		ft_memcpy(tmp, buf->line + cursor - 1, buf->size - cursor);
		ft_memcpy(buf->line + cursor - 1, tmp, buf->size - cursor);
		buf->line[cursor] = 0;
	}
	else
		buf->line[cursor] = 0;
}
