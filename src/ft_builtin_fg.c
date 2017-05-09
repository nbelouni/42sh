/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:23:30 by maissa-b          #+#    #+#             */
/*   Updated: 2017/05/09 09:32:13 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		put_job_in_foreground(t_job *j, int cont);

static int	exec_job_fg(t_job *job)
{
	job->foreground = 1;
	if (job_is_stopped(job))
		continue_job(job, job->foreground); // continue_job(j);
	else
		put_job_in_foreground(job, 0);
	return (0);
}

int      ft_builtin_fg(t_core *core, char **args)
{
	t_job	*job;

	(void)core;
	if (args && args[0])
	{
		if ((job = ft_get_job(args[0])) == NULL)
			return(ft_print_error("42sh: fg: No such job: ", args[0], -1));
	}
	else
	{
		if ((job = get_last_job()) == NULL)
			return (ft_print_error("42sh: fg: ", "current: No such job", -1));
	}
	return (exec_job_fg(job));
}
