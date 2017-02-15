/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/02/15 22:55:01 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_waitchild(char **av, char **envp)
{
	pid_t	pid;
	int		i;
	int		statval;

	pid = fork();
	close_termios();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		wait(&statval);
		waitpid(pid, &status, 0);
	}
	if (pid == 0)
		ft_exec(av, envp);
}
