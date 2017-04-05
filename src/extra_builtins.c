/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:58:54 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/05 09:32:30 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

void			print_pid(t_job *j)
{
	ft_putnbr_fd(j->pgid, 1);
}

void			print_no_opt(t_job *j)
{
	print_state_short(j);
	ft_putstr_fd("\t\t", 1);
	print_command(j);
	ft_putstr_fd("\n", 1);
}

void			print_optl(t_job *j)
{
//	print_index();
	print_current(j);
	ft_putstr_fd("\t", 1);
	print_pgid(j);
	ft_putstr_fd("\t", 1);
	print_state_long(j);
	ft_putstr_fd("\t\t", 1);
	print_command(j);
	ft_putstr_fd("\n", 1);
}

void print_optp(t_job *j)
{
	print_pgid(t_job *j);
	ft_putstr_fd("\n", 1);
}

void			print_state_long(t_job *j)
{
	if (job_is_stopped(j) && !j->notified)
	{
		ft_putstr_fd("Suspended: ", 1);
		ft_putnbr_fd(WSTOPSIG(j->status), 1);
	}
	else if(job_is_completed(j))
	{
		if (WEXITSTATUS(j->status))
		{
			ft_putstr_fd("Exit: ", 1);
			ft_putnbr_fd(WEXITSTATUS(j->status), 1);
		}
		else
			ft_putstr_fd("Done", 1);
	}
	else
		ft_putstr_fd("Running", 1);
}

void			print_state_short(t_job *j)
{
	if (job_is_stopped(j) && !j->notified)
		ft_putstr_fd("Stopped", 1);
	else if(job_is_completed(j))
		ft_putstr_fd("Done", 1);
	else
		ft_putstr_fd("Running", 1);
}

void			print_command(t_job *j)
{
	ft_putstr_fd(j->command, 1);
}

void			print_current(t_job *j)
{
	(void)j;
	// -- TODO --
	ft_putstr_fd("+", 1);
}

void			(*choose_func(int opt))(t_job *)
{
	if (opt == 'p')
		return(&print_optp);
	else if (opt == 'l')
		return(&print_optl);
	else
		return(&print_no_opt);
}

/*
** --- JOBS ---
**	* Only tha last Opt is used
**		eg : jobs -pl == jobs -l
**	TODO : 
**		* Index not implemented yet
**		* Need to look over print_current, need to found a way to remind 
**			which job is the default one used by fg and bg builtins.
**	LINK: http://pubs.opengroup.org/onlinepubs/9699919799/utilities/jobs.html
**	!!!! : jobs -l %1 -l -l -l -p %3 -- Strange behavior there
*/


static int      ft_builtin_jobs(t_core *core, char **args)
{
	void (*print_func)();
	t_job	*j;
	
	print_func = choose_func(opt);
	if (noarg)
		listiter(t_job *jobList, &print_func);
	else
		while (arg)
		{
			j = list_get_nth(jobList, n);
			if (j)
				print_func(j);
			else
				putstr("no such job");
		}
}

/*
** -- BG --
**	* See Jobs for default target of bg
**
**
**
**
*/

static int      ft_builtin_bg(t_core *core, char **args)
{
	t_job	*j;
	
	j = list_get_nth(jobList, n);
	if (job_is_stopped(j) && !j->foreground)
	{
		j->foreground = 0;
		continue_job(j, j->foreground); // continue_job(j);
	}
	else
		print("already running in background");
}

/*
** -- FG --
**	* See Jobs for default target of bg
**
**
**
**
**
*/

static int      ft_builtin_fg(t_core *core, char **args)
{
	t_job	*j;
	
	j = list_get_nth(jobList, n);
	if (job_is_stopped(j))
	{
		j->foreground = 1;
		continue_job(j, j->foreground); // continue_job(j);
	}
}

			
