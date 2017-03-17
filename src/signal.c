/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/03/17 17:52:36 by alallema         ###   ########.fr       */
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

void		get_sigint(int sig)
{
	if (sig == SIGINT)
	{
//		close_termios();
		ft_putstr_fd("\n42sh.$", 1);
//		signal(SIGINT, SIG_DFL);
	}
	return ;
}

void		get_sig_dfl(void)
{
	signal (SIGINT, SIG_DFL);//2
	signal (SIGQUIT, SIG_DFL);//3
	signal (SIGTSTP, SIG_DFL);//20
	signal (SIGTTIN, SIG_DFL);//21
	signal (SIGTTOU, SIG_DFL);//22
	signal (SIGCHLD, SIG_DFL);//17
}

void		get_sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}
