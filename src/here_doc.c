/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:06:13 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:07:30 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_core	*g_core;
extern t_bool	g_is_here_doc;

int		join_lines(t_buf *buf)
{
	char	*tmp;

	tmp = NULL;
	if (buf->final_line)
	{
		if (!(tmp = ft_strjoin(buf->final_line, "\n")))
			return (ft_print_error("\n21sh", ERR_MALLOC, ERR_EXIT));
		free(buf->final_line);
	}
	if (!(buf->final_line = ft_strjoin(tmp, buf->line)))
		return (ft_print_error("\n21sh", ERR_MALLOC, ERR_EXIT));
	if (tmp)
		ft_strdel(&tmp);
	ft_bzero(buf->line, BUFF_SIZE);
	buf->size = 0;
	return (0);
}

int		read_here_doc(t_buf *buf, t_completion *c, t_token *elem, t_lst *hist)
{
	int		ret_read;

	ret_read = 0;
	while ((ret_read = read_line(buf, c, hist)) != ERR_EXIT)
	{
		close_termios();
		if (!ft_strcmp(elem->word, buf->line) ||
		ret_read == CTRL_D || ret_read == ERR_NEW_CMD)
		{
			ft_strdel(&(elem->word));
			if (buf->final_line)
				if (!(elem->word = ft_strjoin(buf->final_line, "\n")))
					return (ft_print_error("\n21sh", ERR_MALLOC, ERR_EXIT));
			break ;
		}
		else if (buf->line[0])
		{
			if (join_lines(buf) == ERR_EXIT)
				return (ERR_EXIT);
		}
		if (g_core->buf->size == 0)
			return (ERR_NEW_CMD);
		clean_pos_curs();
	}
	return (ret_read);
}

int		here_doc(t_token *elem, t_completion *completion, t_lst *hist)
{
	t_buf	*buf;
	int		ret;

	g_is_here_doc = TRUE;
	set_prompt(PROMPT2, ft_strlen(PROMPT2));
	clean_pos_curs();
	if (!(buf = init_buf()))
	{
		g_is_here_doc = FALSE;
		return (ft_print_error("21sh", ERR_MALLOC, ERR_EXIT));
	}
	if ((ret = read_here_doc(buf, completion, elem, hist)) < 0)
	{
		free_buf(buf);
		g_is_here_doc = FALSE;
		return (ret == ERR_EXIT ? ERR_EXIT : ERR_NEW_CMD);
	}
	if (!elem->word && !(elem->word = ft_strdup("")))
	{
		g_is_here_doc = FALSE;
		return (ft_print_error("\n21sh", ERR_MALLOC, ERR_EXIT));
	}
	set_prompt(PROMPT1, ft_strlen(PROMPT1) + close_termios());
	free_buf(buf);
	return ((g_is_here_doc = FALSE));
}
