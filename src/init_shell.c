/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:08:51 by alallema          #+#    #+#             */
/*   Updated: 2017/03/23 19:55:49 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern int			g_sh_tty;
extern int			g_sh_is;
extern pid_t		g_sh_pgid;

void		init_shell(void)
{
	g_sh_tty = STDIN_FILENO;
	g_sh_is = isatty(g_sh_tty);
	if (g_sh_is)
	{
		while (tcgetpgrp(g_sh_tty) != (g_sh_pgid = getpgrp()))
			kill (- g_sh_pgid, SIGTTIN);
		get_sig_ign();
		g_sh_pgid = getpid();
		if (setpgid(g_sh_pgid, g_sh_pgid) < 0)
		{
			ft_putstr_fd("Couldn't put the shell in its own process group", 2);
			exit (1);
		}
		tcsetpgrp(g_sh_tty, g_sh_pgid);
//		PUT2("\n---shell pgid---\n");
//		E(g_sh_pgid);
//		tcgetattr (shell_terminal, &shell_tmodes);
	}
}
