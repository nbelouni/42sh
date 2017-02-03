/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 23:40:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/03 17:04:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		insert_in_buf(t_buf *buf, int cursor, char *s, size_t len)
{
	char	tmp[buf->size - cursor + 1];

	ft_putstr_fd("____1\n", 2);
	if (buf->size + len >= BUFF_SIZE)
		return ;
	if (cursor < buf->size - 1)
	{
		ft_strncpy(tmp, buf->line + cursor, buf->size - cursor);
		tmp[buf->size - cursor] = 0;
		ft_putstr_fd("\ntmp : ", 2);ft_putstr_fd(tmp, 2);
		ft_strncpy(buf->line + cursor, s, len);
		ft_putstr_fd("\nbuf->line : ", 2);ft_putstr_fd(buf->line, 2);
		ft_strncpy(buf->line + cursor + len, tmp, buf->size - cursor);
		ft_putstr_fd("\nbuf->line : ", 2);ft_putstr_fd(buf->line, 2);
		ft_putstr_fd("\n____4\n", 2);
	}
	else
	{
		ft_putstr_fd("\nbuf->line : ", 2);ft_putstr_fd(buf->line, 2);
		E(buf->size);
		ft_strncpy(buf->line + buf->size, s, len);
		buf->line[buf->size + len] = 0;
		ft_putstr_fd("\nbuf->line : ", 2);ft_putstr_fd(buf->line, 2);
	}
	ft_putstr_fd("\n____5\n", 2);
}
/*
void		delete_in_buf(t_buf *buf, int cursor, size_t len, t_bool go_to_right)
{
	char	tmp[buf->size];

	ft_bzero(tmp, buf->size);
	if (len == 0)
		return ;
	if (go_to_right == FALSE)
	{
		if (cursor == PROMPT_LEN)
			return ;
		if (cursor >= buf->size - 1)
			ft_bzero(buf->line - len, len);
		else
		{
			ft_memcpy(tmp, buf->line + cursor, buf->size - cursor);
			ft_memcpy(buf->line + cursor - len, tmp, buf->size - cursor);
			ft_bzero(buf->line + cursor, len);
		}
	}
	if (go_to_right == TRUE)
	{
		if (cursor >= buf->size - 1)
			return ;
		ft_memcpy(tmp, buf->line + cursor + len, buf->size - cursor - len);
		ft_memcpy(buf->line + cursor - 1, tmp, buf->size - cursor - len);
		ft_bzero(buf->line - len, len);
	}
}*/