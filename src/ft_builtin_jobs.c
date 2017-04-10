/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:28:11 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/10 21:22:37 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#define JOBS_OPT ":l:p:"

/*
** To put somewhere else soon
*/

void			(*choose_func(int flag))(t_job *);
void			print_current(t_job *j);
void			print_command(t_job *j);
void			print_state_short(t_job *j);
void			print_state_long(t_job *j);
void			print_optp(t_job *j);
void			print_optl(t_job *j);
void			print_no_opt(t_job *j);
void			print_pgid(t_job *j);
void print_job(t_job *job);
/**/


static void	put_error_job(char *bad_job)
{
	write(2, "42sh: jobs: ", 12);
	write(2, bad_job, ft_strlen(bad_job));
	write(2, ": No such job\n", 14);
}

t_job			*cmp_job(char *cmd, t_list *job_list)
{
	unsigned int count;
	t_job		*job;

	count = 0;
	job = NULL;
	while (job_list)
	{
		job = job_list->content;
		if (ft_strncmp(job->command, cmd, ft_strlen(cmd)) == 0)
		{
			count++;
			if (count > 1)
				return (NULL);
		}
		job_list = job_list->next;
	}
	if (count == 0)
		return (perror(__func__), NULL);
	else
		return (job);
}

t_job			*ft_get_job(char *arg)
{
	t_job		*job;

	job = NULL;
	if (arg[0] == '%')
	{
		if (arg[1] == '%' || !arg[1])
			job = get_last_job();
		else
		{
	//		if (arg[1] == '+' || arg[1] == '-')   /* Partie si on decide de prendre un job par rapport a sa priorite + ou - */
	//			job = get_prior_job(job_list, arg[1]);
	/*else*/if (ft_strisdigit(&arg[1]))
				job = list_get_nth(job_list, ft_atoi(&(arg[1])));
			else
			{
				job = cmp_job(&(arg[1]), job_list);
			}
		}
	}
	else
	{
		if (ft_strisdigit(&arg[0]))
			job = list_get_nth(job_list, ft_atoi(&arg[0]));
		else
			job = cmp_job(&(arg[0]), job_list);
	}
	return (job);
}

static int	check_all_jobs(char **args, void (*print_func)())
{
	t_job	*job;
	int		i;

	job = NULL;
	i = -1;
	while (args[++i])
	{
		job = ft_get_job(args[i]);
		if (job)
			print_func(job);
		else
			put_error_job(args[i]);
	}
	return (0);
}

static int	check_jobsopt_c(t_opt *opt, int ret)
{
	int		flag;

	flag = 0;
	if (ret == (int)'l')
		flag = ret;
	else if (ret == (int)'p')
		flag = ret;
	else if (ret == (int)'?')
		return (-1);
	else if (ret == (int)':')
		flag = opt->opt_char;
	return (flag);
}

int			ft_builtin_jobs(t_core *core, char **args)
{
	void	(*print_func)();
	int		flag;
	int		ret;
	t_opt	opt;
	
	(void)core;
	init_optstruct(&opt);
	flag = 0; /* cas de l'option sans arg derriere flag = (int)l ou (int)p */
	if (args && args[0])
		while ((ret = ft_getopt(ft_tablen(args), args, JOBS_OPT, &opt)) != -1)
			if ((flag = check_jobsopt_c(&opt, ret)) == -1)
				return (-1);
	print_func = choose_func(flag);
	if (!(args[opt.opt_ind]) || !(args && args[0]))
		list_iter(job_list, print_func);
	else
		check_all_jobs(&(args[opt.opt_ind]), print_func);
	return (0);
}
