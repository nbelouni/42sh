/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 14:44:38 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:36:32 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		find_prev_word(t_buf *buf)
{
	int	len;

	len = 0;
	while (get_curs() - len > (int)get_prompt_len()
	&& buf->line[get_curs() - get_prompt_len() - len - 1] == ' ')
		len++;
	while (get_curs() - len > (int)get_prompt_len()
	&& buf->line[get_curs() - get_prompt_len() - len - 1] != ' ')
		len++;
	return (len);
}

int		find_next_word(t_buf *buf)
{
	int	len;

	len = 0;
	while ((get_curs() + len) < (int)get_prompt_len() + buf->size
	&& buf->line[get_curs() - get_prompt_len() + len] != ' ')
		len++;
	while ((get_curs() + len) < (int)get_prompt_len() + buf->size
	&& buf->line[get_curs() - get_prompt_len() + len] == ' ')
		len++;
	return (len);
}

size_t	calc_len(t_buf *buf, int x)
{
	size_t	len;

	len = 0;
	if (x == RIGHT && (get_curs() - get_prompt_len()) < (size_t)buf->size)
		return (1);
	else if ((x == LEFT || x == DEL) && (get_curs() - get_prompt_len()) > 0)
		return (1);
	if (x == HOME || x == CTRL_A || x == CTRL_K)
		len = get_curs() - get_prompt_len();
	else if (x == END || x == CTRL_F || x == CTRL_W)
	{
		if (((buf->size - get_curs() + get_prompt_len()) > 0))
			len = buf->size - get_curs() + get_prompt_len();
		else
			len = 0;
	}
	else if (x == ALT_LEFT || x == CTRL_L || x == CTRL_B)
		len = find_prev_word(buf);
	else if (x == ALT_RIGHT || x == CTRL_N || x == CTRL_E)
		len = find_next_word(buf);
	return (len);
}
