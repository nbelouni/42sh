/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_ended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 16:50:08 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 22:29:16 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			is_line_ended(t_buf *buf)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(buf->final_line, buf->line)))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	ft_strdel(&(buf->final_line));
	buf->final_line = tmp;
	return (0);
}

int		complete_final_line(t_buf *buf, t_token *lst)
{
	t_token	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	if (!lst || !buf->line[0])
		return (0);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	if (count_prev_char(tmp->word, ft_strlen(tmp->word) - 1, '\\') % 2 == 1)
		return (0);
	if (!(tmp2 = ft_strjoin(buf->final_line, " ")))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	ft_strdel(&(buf->final_line));
	buf->final_line = tmp2;
	return (0);
}
