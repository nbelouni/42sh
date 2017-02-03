/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 00:00:38 by alallema          #+#    #+#             */
/*   Updated: 2017/02/04 00:03:34 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_del(size_t len)
{
	E(g_curs.col);X('\n');
	while (len > 0)
	{
		m_left(1);
		t_puts("dm", 1);
		t_puts("dc", 1);
		t_puts("ed", 1);
		len--;
	}
	E(g_curs.col);X('\n');X('\n');
}

void	clean_line(void)
{
	t_puts("sc", 1);
	t_puts("cd", 1);
	t_puts("rc", 1);
}

void	print_post_curs(t_buf *buf)
{
	clean_line();
	int		i;

	i = 0;
	t_puts("sc", 1);
	while (buf->line[(g_curs.win_col * g_curs.row) + g_curs.col -PROMPT_LEN + i])
	{
		ft_putchar_fd(buf->line[((g_curs.win_col * g_curs.row) + g_curs.col - PROMPT_LEN) + i], 1);
		i++;
	}
	t_puts("rc", 1);
}
