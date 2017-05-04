/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/05/03 17:03:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_core	*g_core;

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

void		update_status(void);

void		sigchld_handler(int sigchld)
{
	(void)sigchld;
	update_status();
//	do_job_notification();
}

void		get_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_bzero(g_core->buf->line, BUFF_SIZE);
		ft_putstr_fd("\n42sh.$ ", 1);
	}
	return ;
}

void		init_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, get_sigint);
}
