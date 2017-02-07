/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/07 00:54:58 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_buf	*buf;

	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_curs();
	while (read_line(buf) > ERR_EXIT)
	{
		close_termios();
		if (is_line_ended(buf) >= 0)
		{
			PUT1(buf->final_line);
			X('\n');
//			parse();
			ft_strdel(&(buf->final_line));
		}
		else
		{
			PUT1(buf->final_line);
			X('\n');
		}
		ft_bzero(buf->line, (size_t)(sizeof(char) * BUFF_SIZE));
		buf->size = 0;
		clean_pos_curs();
	}
	close_termios();
	free_buf(buf);
	return (0);
}
