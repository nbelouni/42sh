/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:08:51 by alallema          #+#    #+#             */
/*   Updated: 2017/05/08 20:03:47 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int				g_sh_tty;
int				g_sh_is;
pid_t			g_sh_pgid;
sigset_t		g_original_set;

#define MAXJOBS 30

/*
** The value of this symbolic constant is the total number of signals defined.
** Since the signal numbers are allocated consecutively,
** NSIG is also one greater than the largest defined signal number.
**
** https://www.gnu.org/software/libc/manual/html_node/Standard-Signals.html
*/

#define		ORIG_SIG_LEN	23
/*static */sig_t	g_originals[ORIG_SIG_LEN];
//extern sig_t	*g_originals;

void		block_signal(int sig, sigset_t *set, sigset_t *oset)
{
//	sigemptyset : fonction interdite (man 3)
	sigemptyset(set);

//	sigaddset : fonction interdite (man 3)
	sigaddset(set, sig);

//	sigemptyset : fonction interdite (man 3)
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


void		save_originals_handler(void)
{
	int		i;

	i = 1;
	while (i < ORIG_SIG_LEN)
	{
		if ((g_originals[i] = signal(i, SIG_DFL)) == SIG_ERR)
			g_originals[i] = NULL;
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
	while (i < ORIG_SIG_LEN)
	{
		if (signal(i, g_originals[i]) == SIG_ERR)
			;
		i++;
	}
}

void		init_shell(void)
{

//	sigemptyset : fonction interdite (man 3)
	sigemptyset(&g_original_set);

	sigprocmask(SIG_BLOCK, NULL, &g_original_set);

//	sigdelset : fonction interdite (man 3)
	sigdelset(&g_original_set, SIGCHLD);

	save_originals_handler();
	g_sh_tty = STDIN_FILENO;
	g_sh_is = isatty(g_sh_tty);
	if (g_sh_is)
	{

//	tcgetpgrp : fonction interdite (man 3)
		while (tcgetpgrp(g_sh_tty) != (g_sh_pgid = getpgrp()))
			kill(-g_sh_pgid, SIGTTIN);
		g_sh_pgid = getpid();
		init_signal();
		if (setpgid(g_sh_pgid, g_sh_pgid) < 0)
		{
			ft_putstr_fd("Couldn't put the shell in its own process group", 2);
			exit(1);
		}

//	tcsetpgrp : fonction interdite (man 3)
		tcsetpgrp(g_sh_tty, g_sh_pgid);
	}
	signal(SIGCHLD, sigchld_handler);
}
