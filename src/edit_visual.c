/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 00:00:38 by alallema          #+#    #+#             */
/*   Updated: 2017/03/05 20:12:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	reset_cursor(int i, int cursor)
{
	int		w_col;

	w_col = g_curs.win_col;
	if (w_col == 0)
		w_col = 1;
	while (i > 0)
	{
		if ((cursor + i + get_prompt_len()) % w_col > 0 ||
		((cursor + i + get_prompt_len()) / w_col == 0
		&& cursor > (int)get_prompt_len()))
			t_puts("le", 1);
		else if ((cursor + i + get_prompt_len()) / w_col > 0)
		{
			t_puts("up", 1);
			tputs(tgoto(tgetstr("ch", NULL), 0, w_col - 1), 1, t_putchar);
		}
		i--;
	}
}

void	print_post_curs(t_buf *buf)
{
	int		i;
	int		cursor;

	cursor = (g_curs.win_col * g_curs.row) + g_curs.col - get_prompt_len();
	i = 0;
	t_puts("cd", 1);
	while (buf->line[cursor + i])
	{
		ft_putchar_fd(buf->line[cursor + i], 1);
		if ((cursor + get_prompt_len() + i + 1) %
		((g_curs.win_col) ? g_curs.win_col : 1) == 0)
		{
			t_puts("cr", 1);
			t_puts("do", 1);
		}
		i++;
	}
	if (i > 0)
		reset_cursor(i, cursor);
}

void	print_pre_curs(t_buf *buf)
{
	int		i;
	int		cursor;

	cursor = (g_curs.win_col * g_curs.row) + g_curs.col - get_prompt_len();
	i = 0;
	t_puts("cd", 1);
	while (i < cursor && i < buf->size)
	{
		ft_putchar_fd(buf->line[i], 1);
		i++;
	}
}
