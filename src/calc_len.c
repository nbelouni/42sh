/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 14:44:38 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/05 14:54:17 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		find_prev_word(t_buf *buf, size_t cursor)
{
	int	len;

	len = 0;
	while (cursor - len > ft_strlen(PROMPT1)
	&& buf->line[cursor - ft_strlen(PROMPT1) - len - 1] == ' ')
		len++;
	while (cursor - len > ft_strlen(PROMPT1)
	&& buf->line[cursor - ft_strlen(PROMPT1) - len - 1] != ' ')
		len++;
	return (len);
}

int		find_next_word(t_buf *buf, size_t cursor)
{
	int	len;

	len = 0;
	while ((cursor + len) < ft_strlen(PROMPT1) + buf->size
	&& buf->line[cursor - ft_strlen(PROMPT1) + len] != ' ')
		len++;
	while ((cursor + len) < ft_strlen(PROMPT1) + buf->size
	&& buf->line[cursor - ft_strlen(PROMPT1) + len] == ' ')
		len++;
	return (len);
}

size_t	calc_len(t_buf *buf, int x)
{
	size_t	len;
	size_t	cursor;

	cursor = g_curs.win_col * g_curs.row + g_curs.col;
	len = 0;
	if (x == RIGHT && (cursor - ft_strlen(PROMPT1)) < (size_t)buf->size)
		return (1);
	else if ((x == LEFT || x == DEL) && (cursor - ft_strlen(PROMPT1) > 0))
		return (1);
	if (x == HOME || x == CTRL_A || x == CTRL_K)
		len = (cursor - ft_strlen(PROMPT1));
	else if (x == END || x == CTRL_F || x == CTRL_W)
	{
		if (((buf->size - cursor + ft_strlen(PROMPT1)) > 0))
			len = (buf->size - cursor + ft_strlen(PROMPT1));
		else
			len = 0;
	}
	else if (x == ALT_LEFT || x == CTRL_I || x == CTRL_B)
		len = find_prev_word(buf, cursor);
	else if (x == ALT_RIGHT || x == CTRL_N || x == CTRL_E)
		len = find_next_word(buf, cursor);
	return (len);
}
