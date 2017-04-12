/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/04/12 04:12:06 by llaffile         ###   ########.fr       */
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

void		sigttou_handler(int sigttou)
{
	sigset_t	set;
	sigset_t	oset;

	(void)sigttou;
	block_signal(SIGTTOU, &set, &oset);
	if (g_sh_pgid == getpid())
		dprintf(2, "in %s FATHER\n", __func__);
	else
		dprintf(2, "in %s SON\n", __func__);
	unblock_signal(&oset);
}

void		sigchld_handler(int sigchld)
{
	(void)sigchld;
	dprintf(2,"recceived sigchld\n");
	do_job_notification();
}

void		get_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_bzero(core->buf->line, BUFF_SIZE);
		ft_putstr_fd("\n42sh.$ ", 1);
	}
	return ;
}

void		init_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, get_sigint);
}
