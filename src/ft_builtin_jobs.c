/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:28:11 by maissa-b          #+#    #+#             */
/*   Updated: 2017/05/03 16:11:45 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#define JOBS_OPT "lp"

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
/**/

extern t_list	*g_job_list;

static void	put_error_job(char *bad_job)
{
	write(1, "42sh: jobs: ", 12);
	write(1, bad_job, ft_strlen(bad_job));
	write(1, ": No such job\n", 14);
}

t_job			*cmp_job(char *cmd, t_list *g_job_list)
{
	unsigned int count;
	t_job		*job;

	count = 0;
	job = NULL;
	while (g_job_list)
	{
		job = g_job_list->content;
		if (ft_strncmp(job->command, cmd, ft_strlen(cmd)) == 0)
		{
			count++;
			if (count > 1)
			{
				ft_putendl("42sh: ambigous job spec: "), ft_putendl(cmd); // FT_PRINT_ERROR
				return (NULL);
			}
		}
		g_job_list = g_job_list->next;
	}
	if (count == 0)
	{
		// put_error_job(cmd);
		return (NULL);
	}
	else
		return (job);
}

static t_job	*ft_get_job_from_arg(char *arg)
{
	if (ft_strisdigit(arg))
	{
		return (list_get_nth(g_job_list, ft_atoi(arg)));
	}
	else
	{
		return (cmp_job(arg, g_job_list));
	}
}

t_job			*ft_get_job(char *arg)
{
	t_job		*job;

	job = NULL;
	if (arg[0] == '%')
	{
		if (!arg || arg[1] == '%' || arg[1] == '+')
			job = get_last_job();
		else
		{
			job = ft_get_job_from_arg(arg + 1);
		}
	}
	else
	{
		if (arg[0] != '\0')
		{
			job = ft_get_job_from_arg(arg);
		}
	}
	return (job);
}

static void	check_all_jobs(char **args, void (*print_func)())
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
}

// static int	check_jobsopt_c(t_opt *opt, int ret, char **args)
// {
// 	void	(*print_func)();
// 	t_job	*job;

// 	job = NULL;
// 	if (ret == (int)'l' || ret == (int)'p')
// 	{
// 		if (args[opt->opt_ind])
// 		{
// 			print_func = (args[opt->opt_ind - 1][ft_strlen(args[opt->opt_ind - 1]) - 1] == 'l') ? &print_optl : &print_optp;
// 			ft_putendl(args[opt->opt_ind + 1]);
// 			check_all_jobs(args + opt->opt_ind, print_func);
// 		}
// 		else
// 			(opt->opt_char == (int)'p') ? list_iter(g_job_list, (void *)print_optp) : list_iter(g_job_list, (void *)print_optl);
// 	}
// 	else
// 	{
// 		return (-1);
// 	}
// 	return (0);
// }

int			ft_builtin_jobs(t_core *core, char **args)
{
	void	(*print_func);
	int		*opt;

	(void)core;
	if (!args || !args[0])
		list_iter(g_job_list, (void *)print_no_opt);
	else
	{	
		if ((opt = ft_opt_parse(JOBS_OPT, args, 1, 0)) == NULL)
			return (ERR_EXIT);
		if (opt[0] == -1)
		{
			free(opt);
			return (-1);
		}
		print_func = (opt[1]) ? choose_func((int)'l') : choose_func((int)'p');
		if (args[opt[0]] != NULL)
			check_all_jobs(&(args[opt[0]]), print_func);
		else
			list_iter(g_job_list, print_func);
		free(opt);
	}
	return (0);
}
	// if (args && args[0])
	// {
	// 	while ((ret = ft_getopt(ft_tablen(args), args, JOBS_OPT, &opt)) != -1)
	// 	{
	// 		if (check_jobsopt_c(&opt, ret, args) == -1)
	// 			return (-1);
	// 	}
	// 	return (0);
	// }
	// list_iter(g_job_list, (void *)print_no_opt);
	// return (0);

	// flag = 0;
	// if (!args || !args[0])
	// {
	// 	print_func = &print_no_opt;
	// 	list_iter(g_job_list, print_func);
	// 	return (0);
	// }
	// while ((ret = ft_getopt(ft_tablen(args), args, JOBS_OPT, &opt)) != -1)
	// {
	// 	if ((flag = check_jobsopt_c(&opt, ret)) == -1)
	// 		return (-1);
	// }
	// print_func = choose_func(flag);
	// if (flag == 0)
	// 	check_all_jobs(args, print_func);
	// else
	// {
	// 	if ((opt.opt_arg) == NULL)
	// 	{
	// 		list_iter(g_job_list, print_func);
	// 	}
	// 	else
	// 	{
	// 		check_all_jobs(&(args[opt.opt_ind]), print_func);
	// 	}
	// }
	// return (0);
