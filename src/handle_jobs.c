/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:15:02 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/21 16:50:50 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"
/*
void	put_job_in_foreground(t_job *j, int cont)
{
  tcsetpgrp (shell_terminal, j->pgid);
  if (cont)
  {
      tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
      if (kill (- j->pgid, SIGCONT) < 0)
        perror ("kill (SIGCONT)");
  }
  wait_for_job (j);
  tcsetpgrp (shell_terminal, shell_pgid);
  tcgetattr (shell_terminal, &j->tmodes);
  tcsetattr (shell_terminal, TCSADRAIN, &shell_tmodes);
}

void	put_job_in_background(t_job *j, int cont)
{
  if (cont)
    if (kill (-j->pgid, SIGCONT) < 0)
      perror ("kill (SIGCONT)");
}
*/

void	doRedir(List_p ioList);
	
void	launch_process(t_process_p process, pid_t pgid, int foreground)
{
  pid_t pid;

  pid = getpid();
  if (pgid == 0) pgid = pid;
  setpgid(pid, pgid);
//  if (foreground)
//	  tcsetpgrp(shell_terminal, pgid);
  doRedir(process->ioList);
  signal (SIGINT, SIG_DFL);
  signal (SIGQUIT, SIG_DFL);
  signal (SIGTSTP, SIG_DFL);
  signal (SIGTTIN, SIG_DFL);
  signal (SIGTTOU, SIG_DFL);
  signal (SIGCHLD, SIG_DFL);
//  execvp(p->argv[0], p->argv);
  perror("execvp");
  exit (1);
}

t_node_p	iterInOrder(t_node_p ptr, List_p *stock)
{
	while (ptr || *stock)
	{
		if (ptr)
		{
			PUSH(stock, ptr);
			ptr = ptr->left;
		}
		else
			return (POP(stock));
	}
	return (NULL);
}

void	doRedir(List_p ioList)
{
	Io_p	io;
	
	while (ioList)
	{
		io = ioList->data;
		if (io->flag & OPEN)
		{
			if (access(io->str, X_OK) == -1)
				io->mode |= O_CREAT;
			in = open(io->str, io->mode);
		}
		if (io->flag & DUP)
			dup2(io->in, io->out);
		if (io->flag & CLOSE)
			close(io->in);
		io = io->next;
	}
}

void	doPipe(t_process *p1, t_process *p2)
{
	int	ioPipe[2];
	Io_p	io_in;
	Io_p	io_out;

	if (pipe(ioPipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	io_in = new_io();
	io_out = new_io();
	io_in->flag |= DUP | CLOSE;
	io_out->flag |= DUP | CLOSE;
	io_in->in = ioPipe[0];
	io_out->in = ioPipe[1];
	io_in->out = STDOUT_FILENO;
	io_out->out = STDIN_FILENO;
	PUSH(&(p1->ioList), new_link(io_in, sizeof(*io_in)));
	PUSH(&(p2->ioList), new_link(io_out, sizeof(*io_out)));
}

int		doFork(t_process p, int pgid, int foreground)
{
	int	pid;
	
	pid = fork ();
	if (pid == 0)
		launch_process (p, pgid, foreground);
	else if (pid < 0)
	{
		perror ("fork");
		exit (1);
	}
	p->pid = pid;
	return (pid);
}

void	doPipeline(t_job *job, List_p pipeline)
{
	int	pid;
	while (pipeline)
	{
		if (pipeline->next)
			doPipe(pipeline->content, pipeline->content->next);
		pid = doFork(pipeline, job->pgid, job->foreground);
		if (job->pgid == 0)
			job->pgid = pid;
		set(pid, job->pgid);
		pipeline = pipeline->next;
	}
}

void	launch_job(t_job *j)
{
  t_node_p	current;
  List_p	stack;

  current = j->process_tree;
  while ((current = iterInOrder(current, &stack)))
  {
	  if (current->type == IF)
		  current = ((current->data->type == IF_OR && last) || (current->data->type == IF_AND && !last))? current->right: NULL;
	  else
		  doPipeline(j, current->data);
  }
  if (foreground)
    put_job_in_foreground(j, 0);
  else
    put_job_in_background(j, 0);
}

/*
  for (p = j->first_process; p; p = p->next)
    {
      if (p->next)
        {
          if (pipe (mypipe) < 0)
            {
              perror ("pipe");
              exit (1);
            }
          outfile = mypipe[1];
        }
      else
        outfile = j->stdout;

      pid = fork ();
      if (pid == 0)
        launch_process (p, j->pgid, infile,
                        outfile, j->stderr, foreground);
      else if (pid < 0)
        {
          perror ("fork");
          exit (1);
        }
      else
        {
          p->pid = pid;
          if (shell_is_interactive)
            {
              if (!j->pgid)
                j->pgid = pid;
              setpgid (pid, j->pgid);
            }
        }


      if (infile != j->stdin)
        close (infile);
      if (outfile != j->stdout)
        close (outfile);
      infile = mypipe[0];
    }
*/
