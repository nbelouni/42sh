#include "42sh.h"

// step 1 : parse options
// step 2 : check args
// step 3 with args : get each jobs identified with each args
// step 3 without args : get each jobs
// step 4 : print jobs

/////////////////////////////////////// BUILTIN JOBS /////////////////////////////////////////////////////

#define JOBS_OPT ":l:p:"

static void	put_error_job(char *bad_job)
{
	write(2, "42sh: jobs: ", 12);
	write(2, bad_job, ft_strlen(bad_job));
	write(2, ": No such job\n", 14);
}

t_job			*get_prior_job(t_job *job, char c)
{
	t_job		tmp;

	tmp = job;
	while (tmp)
	{
		if (tmp->prior == (int)c)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_job	*ft_get_job(t_job *jobList, char *arg)
{
	t_job		*job;

	job = NULL;
	if (arg[0] == '%')
	{
		if (arg[1] == '%' || !arg[1])
		{
			job = get_prior_job(jobList, '+');
		}
		else
		{
			// if (arg[1] == '+' || arg[1] == '-')   /* Partie si on decide de prendre un job par rapport a sa priorite + ou - */
			// {
			// 	job = get_prior_job(jobList, arg[1]);
			// }
			if (ft_strisdigit(&arg[1]))
				job = list_get_nth(jobList, ft_atoi(&(arg[1])));
		}
	}
	else
	{
		if (ft_strisdigit(&arg[0]))
			job = list_get_nth(jobList, ft_atoi(&arg[0]));
	}
	return (job);
}

static int	ft_builtin_jobs(t_core *core, char **args)
{
	void	(*print_func)();
	int		flag;
	int		ret;
	t_job	*j;
	t_opt	opt;
	
	(void)core;
	if (!args || !args[0])
		listiter(jobList, &print_no_opt);
	else
	{
		flag = 0; /* cas de l'option sans arg derriere flag = (int)l ou (int)p */
		while ((ret = ft_getopt(ft_tablen(args)), argv, JOBS_OPT, &opt) != -1)
		{
			if (ret == (int)'l')
				flag = ret;
			else if (ret == (int)'p')
				flag = ret;
			else if (ret == (int)'?')
				return (-1);
			else if (ret == (int)':')
				flag = opt->opt_char;
		}
		print_func = choose_func(flag);
		flag = 0;
		if (!args || !(args[opt->opt_ind]))
		{
			listiter(jobList, &print_func);
		}
		else
		{
			while (args[n])
			{
				j = ft_get_job(jobList, args[flag]);
				if (j)
					print_func(j);
				else
					put_error_job(args[flag]);
				++flag;
			}
		}
	}
}

/////////////////////////////////////// BUILTIN BG /////////////////////////////////////////////////////

static int		exec_job_bg(t_job *j)
{
	if (job_is_stopped(j) && !j->foreground)
	{
		j->foreground = 0;
		continue_job(j, j->foreground); // continue_job(j);
	}
	else
	{
		print("already running in background");
		return (-1);
	}
	return (0);
}

int      ft_builtin_bg(t_core *core, char **args)
{
	t_job	*j;
	
	(void)core;
	if (args && args[0])
	{
		j = ft_get_job(jobList, args[0]);
		exec_job_bg(j);
	}
	else
	{
		j = jobList;
		while (j)
		{
			exec_job_bg(j);
			j = j->next;
		}
	}
	return (0);
}

/////////////////////////////////////// BUILTIN FG /////////////////////////////////////////////////////

static int	exec_job_fg(t_job *j)
{
	if (job_is_stopped(j))
	{
		j->foreground = 1;
		continue_job(j, j->foreground); // continue_job(j);
	}
	return (0);
}

int      ft_builtin_fg(t_core *core, char **args)
{
	t_job	*j;
	
	(void)core
	if (args && args[0])
	{
		while (*args)
		{
			j = ft_get_job(jobList, *args);
			exec_job_fg(j);
			args++;
		}
	}
	else
	{
		j = jobList;
		while (j)
		{
			exec_job_fg(j);
			j = j->next;
		}
	}
}