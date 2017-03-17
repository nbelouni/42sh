/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:53:12 by alallema          #+#    #+#             */
/*   Updated: 2017/03/17 22:28:04 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		restore_fd(int in_fd, int out_fd, int err_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (err_fd != STDERR_FILENO)
	{
		dup2(err_fd, STDERR_FILENO);
		close(err_fd);
	}
}

void		launch_process (t_process_p p, pid_t pgid,
		int fd[2], int err_fd,
		int foreground, t_lst *env)
{
	pid_t	pid;

	(void)foreground;
	if (get_sh()->is)
	{
		pid = getpid();
		if (pgid == 0)
		{
			pgid = pid;
			setpgid(pid, pgid);
		}
//		if (foreground)
//			tcsetpgrp(sh->tty, pgid);
		get_sig_dfl();
	}
	restore_fd(fd[0], fd[1], err_fd);
	ft_exec(p->argv, env);
}
