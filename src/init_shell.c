/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:08:51 by alallema          #+#    #+#             */
/*   Updated: 2017/03/17 22:14:56 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_sh		*get_sh(void)
{
	static t_sh	sh;

	return (&sh);
}

void		init_shell(void)
{
	t_sh	*sh;

	sh = get_sh();
	sh->tty = STDIN_FILENO;
	sh->is = isatty(sh->tty);
	if (sh->is)
	{
		while (tcgetpgrp(sh->tty) != (sh->pgid = getpgrp()))
			kill (- sh->pgid, SIGTTIN);
		get_sig_ign();
		sh->pgid = getpid();
		if (setpgid(sh->pgid, sh->pgid) < 0)
		{
			ft_putstr_fd("Couldn't put the shell in its own process group", 2);
			exit (1);
		}
		tcsetpgrp(sh->tty, sh->pgid);
		E(sh->pgid);
	}
}
