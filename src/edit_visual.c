/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 00:00:38 by alallema          #+#    #+#             */
/*   Updated: 2017/02/04 21:47:44 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_del(size_t len)
{
	while (len > 0)
	{
		m_left(1);
		t_puts("dm", 1);
		t_puts("dc", 1);
		t_puts("ed", 1);
		len--;
	}
}

void	print_post_curs(t_buf *buf, t_bool insert_mode)
{
	int		i;
	int		cursor;

	(void)insert_mode;
	cursor = (g_curs.win_col * g_curs.row) + g_curs.col - PROMPT_LEN;
	i = 0;
	t_puts("cd", 1);
	while (buf->line[cursor + i])
	{
		ft_putchar_fd(buf->line[((g_curs.win_col * g_curs.row) + g_curs.col - PROMPT_LEN) + i], 1);
		if ((cursor + PROMPT_LEN + i + 1) % g_curs.win_col == 0)
		{
			t_puts("cr", 1);
			t_puts("do", 1);
		}
		i++;
	}
	if (i > 0)
	{
		while (i > 0)
		{
			if ((cursor + i + PROMPT_LEN) % g_curs.win_col > 0 || 
			((cursor + i + PROMPT_LEN) / g_curs.win_col == 0 && cursor > PROMPT_LEN))
				t_puts("le", 1);
			else if ((cursor + i + PROMPT_LEN) / g_curs.win_col > 0)
			{
				t_puts("up", 1);
				tputs(tgoto(tgetstr("ch", NULL), 0, g_curs.win_col - 1), 1, t_putchar);
			}
			i--;
		}
	}
}
