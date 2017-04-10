/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:08:51 by alallema          #+#    #+#             */
/*   Updated: 2017/04/10 08:45:34 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern int			g_sh_tty;
extern int			g_sh_is;
extern pid_t		g_sh_pgid;
sigset_t			originalSet;
volatile sig_atomic_t	sigwinch_n;
# define MAXJOBS	30

void		sigchld_handler(int sigchld);


static sig_t	originals[NSIG];

void		init_signal()
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, get_sigint);
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
		signal(i, originals[i]);
		i++;
	}
	originals[SIGTSTP] = SIG_DFL;
	originals[SIGTTIN] = SIG_DFL;
	originals[SIGTTOU] = SIG_DFL;
}

void		restoreOriginalsHandler()
{
	int		i;

	i = 1;
	while (i < NSIG)
	{
		if (signal(i, originals[i]) == SIG_ERR)
			perror(__func__);
		i++;
	}
}

void		init_shell(void)
{
	sigemptyset(&originalSet);
	sigprocmask(SIG_BLOCK, NULL, &originalSet);
	sigdelset(&originalSet, SIGCHLD);
	saveOriginalsHandler();
	g_sh_tty = STDIN_FILENO;
	g_sh_is = isatty(g_sh_tty);
	if (g_sh_is)
	{
		while (tcgetpgrp(g_sh_tty) != (g_sh_pgid = getpgrp()))
			kill (- g_sh_pgid, SIGTTIN);
		init_signal();
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
		signal(SIGCHLD, sigchld_handler);
}
