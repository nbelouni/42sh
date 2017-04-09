/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/04/09 05:22:25 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_bool		get_win(void)
{
	struct winsize	windows;

	if (ioctl(0, TIOCGWINSZ, &windows) < 0)
		return (FALSE);
	g_curs.win_col = windows.ws_col;
	g_curs.win_row = windows.ws_row;
	return (TRUE);
}

void		get_sigwinch(int sig)
{
	int		status;

	waitpid(-1, &status, 0);
	if (sig == SIGWINCH)
		get_win();
	return ;
}

void		sigchld_handler(int sigchld)
{
	(void)sigchld;
	do_job_notification();
}

void		get_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_bzero(core->buf->line, BUFF_SIZE);
//		sigaddset(set->sig_set, SIGINT);
		ft_putstr_fd("\n42sh.$ ", 1);
	}
	return ;
}
