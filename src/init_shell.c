/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:08:51 by alallema          #+#    #+#             */
/*   Updated: 2017/04/12 03:57:33 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern int				g_sh_tty;
extern int				g_sh_is;
extern pid_t			g_sh_pgid;
sigset_t				g_original_set;

#define MAXJOBS 30

/*static */sig_t	g_originals[NSIG];
//extern sig_t	*g_originals;

void		block_signal(int sig, sigset_t *set, sigset_t *oset)
{
	sigemptyset(set);
	sigaddset(set, sig);
	sigemptyset(oset);
	sigprocmask(SIG_BLOCK, set, oset);
}

void		unblock_signal(sigset_t *oset)
{
	sigprocmask(SIG_SETMASK, oset, (sigset_t *)NULL);
}

sig_t	*getOriginals()
{
	return (g_originals);
}

void	sigttou_handler(int sigttou);

void		save_originals_handler(void)
{
	int		i;

	i = 1;
	dprintf(2, "%s %p %p\n", __func__, g_originals, &g_originals);
	while (i < NSIG)
	{
		if ((g_originals[i] = signal(i, SIG_IGN)) == SIG_ERR)
		{
			perror(__func__);
			g_originals[i] = NULL;
		}
		signal(i, g_originals[i]);
		i++;
	}
	g_originals[SIGTSTP] = SIG_DFL;
	g_originals[SIGTTIN] = SIG_DFL;
	g_originals[SIGTTOU] = SIG_DFL;
}

void		restore_originals_handler(void)
{
	int		i;

	i = 1;
	while (i < NSIG)
	{
		if (signal(i, g_originals[i]) == SIG_ERR)
			perror(__func__);
		i++;
	}
}

void		init_shell(void)
{
	sigemptyset(&g_original_set);
	sigprocmask(SIG_BLOCK, NULL, &g_original_set);
	sigdelset(&g_original_set, SIGCHLD);
	save_originals_handler();
	g_sh_tty = STDIN_FILENO;
	g_sh_is = isatty(g_sh_tty);
	if (g_sh_is)
	{
		while (tcgetpgrp(g_sh_tty) != (g_sh_pgid = getpgrp()))
			kill(-g_sh_pgid, SIGTTIN);
		g_sh_pgid = getpid();
		init_signal();
		if (setpgid(g_sh_pgid, g_sh_pgid) < 0)
		{
			ft_putstr_fd("Couldn't put the shell in its own process group", 2);
			exit(1);
		}
		tcsetpgrp(g_sh_tty, g_sh_pgid);
	}
	signal(SIGCHLD, sigchld_handler);
}
