/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 20:18:50 by alallema          #+#    #+#             */
/*   Updated: 2017/03/17 22:31:54 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static void		wait_process(t_job *j, t_process_p process, int *fd, t_lst *env)
{
	pid_t	pid;
	int		status;

	(void)fd;
	pid = fork ();
	close_termios();
	if (pid < 0)
	{
		ft_putstr_fd("error fork", 2);
		exit (1);
	}
	if (pid > 0)
	{
		process->pid = pid;
		waitpid(pid, &status, 0);
		if (get_sh()->is)
		{
			if (!j->pgid)
				j->pgid = pid;
			setpgid(pid, j->pgid);
		}
	}
	if (pid == 0)
	{
		PUT2("--lanch_process--\n");
		launch_process(process, j->pgid, fd, STDERR_FILENO, j->foreground, env);
	}
}

void		launch_pipeline(t_job *job, t_list *process_lst, t_lst *env)
{
	int			pipefd[2];
	int			fd[2];

	fd[0] = STDIN_FILENO;
	while (process_lst)
	{
		if (process_lst->next)
		{
			if (pipe(pipefd) < 0)
			{
				ft_putstr_fd("error pipe", 2);
				exit (1);
			}
			fd[1] = pipefd[1];
		}
		else
			fd[1] = STDOUT_FILENO;
		wait_process(job, process_lst->content, fd, env);
		if (fd[0] != STDIN_FILENO)
			close (fd[0]);
		if (fd[1] != STDOUT_FILENO)
			close (fd[1]);
		fd[0] = pipefd[0];
		process_lst = process_lst->next;
	}
}

void		launch_job(t_list *list, t_lst *env)
{
	t_list		*job_list;
	t_job		*job;
	t_node_p	process_tree;
	t_sh		*sh;

	sh = get_sh();
	job_list = list;
	while (list)
	{
		PUT2("\n--list--\n");
		job = list->content;
		process_tree = job->process_tree;
		if (process_tree->type == IF)
		{
			PUT2("\n---condition--\n");
		}
		if (process_tree->type == PROCESS)
		{
			PUT2("\n--launch_pipeline--\n");
			launch_pipeline(job, process_tree->data, env);
		}
		list = list->next;
	}
/*	if (!sh->is)
		wait_job(j);
	else if (foreground)
		put_job_in_foreground (j, 0);
	else
		put_job_in_background (j, 0);
*/}
