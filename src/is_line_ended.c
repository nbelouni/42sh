/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_ended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 16:50:08 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/18 00:21:24 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			is_line_ended(t_buf *buf, int x)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(buf->final_line, buf->line)))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	free(buf->final_line);
	buf->final_line = 0;
	buf->final_line = tmp;
	if (x)
	{
		set_prompt(PROMPT2, ft_strlen(PROMPT2));
		return (ERR_NEW_CMD);
	}
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	return (TRUE);
}
