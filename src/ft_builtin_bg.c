/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:13:35 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/10 19:05:46 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int		exec_job_bg(t_job *job)
{
	if (job == NULL)
		return (-1);
	dprintf(2, "state of foreground <%d> and is it stopped <%d>\n", job->foreground, job_is_stopped(job));
	if (job_is_stopped(job) && job->foreground)
	{
		job->foreground = 0;
		continue_job(job, job->foreground); // continue_job(j);
	}
	else
	{
		write(2, "42sh: bg: job already in background\n", 36);
		return (-1);
	}
	return (0);
}

int      ft_builtin_bg(t_core *core, char **args)
{
	t_job	*job;

	(void)core;
	if (args && args[0])
	{
		if ((job = ft_get_job(args[0])) == NULL)
			return(ft_print_error("42sh: bg: No such job: ", args[0], -1));
	}
	else
	{
		if ((job = get_last_job()) == NULL)
			return (ft_print_error("42sh: bg: ", "current: No such job", -1));
	}
	return (exec_job_bg(job));
}
