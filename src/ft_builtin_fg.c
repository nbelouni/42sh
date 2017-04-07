/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:23:30 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/07 19:27:59 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int	exec_job_fg(t_job *job)
{
	if (job_is_stopped(job))
	{
		job->foreground = 1;
		continue_job(job, job->foreground); // continue_job(j);
	}
	return (0);
}

int      ft_builtin_fg(t_core *core, char **args)
{
	(void)core;
	if (args && args[0])
	{
		exec_job_fg(ft_get_job(args[0]));
	}
	else
	{
		exec_job_fg(get_last_job());
	}
	return (0);
}
