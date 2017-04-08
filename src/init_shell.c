/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:08:51 by alallema          #+#    #+#             */
/*   Updated: 2017/04/08 18:09:08 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern int			g_sh_tty;
extern int			g_sh_is;
extern pid_t		g_sh_pgid;

void		set_signal(void)
{
	sigset_t		*sig_set;

	sig_set = ft_memalloc(sizeof(sigset_t));
	core->sig_set = sig_set;
	sigemptyset(core->sig_set);
	sigaddset(core->sig_set, SIGQUIT);
	sigaddset(core->sig_set, SIGTSTP);
	sigaddset(core->sig_set, SIGTTIN);
	sigaddset(core->sig_set, SIGTTOU);
	sigaddset(core->sig_set, SIGCHLD);
}

void		init_shell(void)
{
	g_sh_tty = STDIN_FILENO;
	g_sh_is = isatty(g_sh_tty);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (g_sh_is)
	{
		while (tcgetpgrp(g_sh_tty) != (g_sh_pgid = getpgrp()))
			kill(-g_sh_pgid, SIGTTIN);
		set_signal();
		if (sigprocmask(SIG_BLOCK, core->sig_set, NULL) < 0)
			return ;/*ERROR a set*/
		g_sh_pgid = getpid();
		if (setpgid(g_sh_pgid, g_sh_pgid) < 0)
		{
			ft_putstr_fd("Couldn't put the shell in its own process group", 2);
			exit(1);
		}
		tcsetpgrp(g_sh_tty, g_sh_pgid);
	}
}
