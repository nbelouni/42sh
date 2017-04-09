/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:08:51 by alallema          #+#    #+#             */
/*   Updated: 2017/04/09 05:23:52 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern int			g_sh_tty;
extern int			g_sh_is;
extern pid_t		g_sh_pgid;
sigset_t			oset;
volatile sig_atomic_t	sigwinch_n;
# define MAXJOBS	30


static sig_t	originals[NSIG];

void		set_signal()
{
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

void		blockSignal(int sig, sigset_t *set, sigset_t *oset)
{
	sigemptyset(set);
	sigaddset(set, sig);
	sigemptyset(oset);
	sigprocmask(SIG_BLOCK, set, oset);
}

void	unblockSignal(sigset_t *oset)
{
	sigprocmask (SIG_SETMASK, oset, (sigset_t *)NULL);
}

void		saveOriginalsHandler()
{
	int		i;

	i = 1;
	while (i < NSIG)
	{
		if ((originals[i] = signal(i, SIG_IGN)) == SIG_ERR){
			perror(__func__);
//			printf("%p amd <%d>\n", originals[i], i);
		}
		originals[i] = signal(i, SIG_IGN);
		i++;
	}
}

void		restoreOriginalsHandler()
{
	int		i;

	i = 1;
	while (i < NSIG)
	{
		if ((originals[i] = signal(i, SIG_IGN)) == SIG_ERR)
			perror(__func__);
		i++;
	}
}

void		init_shell(void)
{
	sigemptyset(&oset);
	sigprocmask(SIG_BLOCK, NULL, &oset);
	sigdelset(&oset, SIGCHLD);
	saveOriginalsHandler();
	g_sh_tty = STDIN_FILENO;
	g_sh_is = isatty(g_sh_tty);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, get_sigint);
	if (g_sh_is)
	{
		while (tcgetpgrp(g_sh_tty) != (g_sh_pgid = getpgrp()))
			kill (- g_sh_pgid, SIGTTIN);
		set_signal();
		if (sigprocmask(SIG_BLOCK, core->sig_set, NULL) < 0)
			return ;
		g_sh_pgid = getpid();
		if (setpgid(g_sh_pgid, g_sh_pgid) < 0)
		{
			ft_putstr_fd("Couldn't put the shell in its own process group", 2);
			exit (1);
		}
		tcsetpgrp(g_sh_tty, g_sh_pgid);
//		tcgetattr (shell_terminal, &shell_tmodes);
	}
}
