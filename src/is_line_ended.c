/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_ended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 16:50:08 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/24 16:28:52 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	C'est en chantier, je mets au propre apres le push
*/
int			is_line_ended(t_buf *buf)
{
	char	*tmp;
/*	int		i;
	t_bool	add_dot;

	i = ft_strlen(buf->final_line);
	add_dot = TRUE;
	while (--i >= 0)
	{
		if (buf->final_line[i] != ' ')
		{	
			if (is_separator(buf->final_line, i))
				add_dot = FALSE;
			break;
		}
	}
	if (buf->final_line && add_dot == TRUE)
	{
		if (!(tmp = ft_strjoin(buf->final_line, ";")))
			return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
		free(buf->final_line);
		buf->final_line = tmp;
	}
*/	if (!(tmp = ft_strjoin(buf->final_line, buf->line)))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	free(buf->final_line);
	buf->final_line = tmp;
	return (0);
}
