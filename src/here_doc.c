/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 19:55:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/17 18:13:02 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		join_lines(t_buf *buf)
{
	char	*tmp;

	tmp = NULL;
	if (buf->final_line)
	{
		if (!(tmp = ft_strjoin(buf->final_line, "\n")))
			return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
		free(buf->final_line);
	}
	if (!(buf->final_line = ft_strjoin(tmp, buf->line)))
		return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
	if (tmp)
		ft_strdel(&tmp);
	ft_bzero(buf->line, BUFF_SIZE);
	return (0);
}

int		read_here_doc(t_buf *buf, t_completion *completion, t_token *elem, t_lst *hist)
{
	int		ret_read;

	ret_read = 0;
	while ((ret_read = read_line(buf, completion, hist)) != ERR_EXIT)
	{
		close_termios();
		if (!ft_strcmp(elem->word, buf->line))
		{
			ft_strdel(&(elem->word));
			if (buf->final_line)
			{
				if (!(elem->word = ft_strdup(buf->final_line)))
					return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
			}
			break ;
		}
		else if (buf->line[0])
		{
			if (join_lines(buf) == ERR_EXIT)
				return (ERR_EXIT);
		}
		clean_pos_curs();
	}
	return (ret_read);
}

int		here_doc(t_token *elem, t_completion *completion, t_lst *hist)
{
	t_buf	*buf;

	set_prompt(PROMPT2, ft_strlen(PROMPT2));
	clean_pos_curs();
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	if (read_here_doc(buf, completion, elem, hist) == ERR_EXIT)
		return (ERR_EXIT);
	if (!elem->word)
	{
		if (!(elem->word = ft_strdup("")))
			return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
	}
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	close_termios();
	free_buf(buf);
	return (0);
}
