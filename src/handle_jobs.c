/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:15:02 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/22 13:09:43 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

static void		put_job_in_background(t_job *j, int cont)
{
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
}

static void		put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp (g_sh_tty, j->pgid);

	if (cont)
	{
//		tcsetattr (g_sh_tty, TCSADRAIN, &j->tmodes);
		if (kill(- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
//	wait_for_job (j);
	/* Put the shell back in the foreground.  */
	tcsetpgrp (g_sh_tty, g_sh_pgid);

//	/* Restore the shell’s terminal modes.  */
//	tcgetattr (g_sh_tty, &j->tmodes);
//	tcsetattr (g_sh_tty, TCSADRAIN, &shell_tmodes);
}

void	doRedir(Io_p io);

void	launch_process(t_process_p process, pid_t pgid, int foreground)
{
  pid_t pid;

  (void)foreground;
  pid = getpid();
  if (pgid == 0) pgid = pid;
  setpgid(pid, pgid);
  if (foreground)
	tcsetpgrp(g_sh_tty, pgid);
//  doRedir(process->ioList);
  list_iter(process->ioList, (void *)doRedir);
  signal (SIGINT, SIG_DFL);
  signal (SIGQUIT, SIG_DFL);
  signal (SIGTSTP, SIG_DFL);
  signal (SIGTTIN, SIG_DFL);
  signal (SIGTTOU, SIG_DFL);
  signal (SIGCHLD, SIG_DFL);
  ft_check_exec(process->argv);
// execvp(p->argv[0], p->argv);
// perror("execvp");
  exit (1);
}

t_node_p	iterInOrder(t_node_p ptr, List_p *stock)
{
	while (ptr || *stock)
	{
		PUT2("up\n");
		if (ptr)
		{
			PUT2("mid\n");
			PUSH(stock, ptr);
			ptr = ptr->left;
		}
		else
		{
			PUT2("bot\n");
			return (POP(stock));
		}
	}
	return (NULL);
}

void	doRedir(Io_p io)
{
	if (io->flag & OPEN)
	{
		if (access(io->str, X_OK) == -1)
			io->mode |= O_CREAT;
		io->in = open(io->str, io->mode);
	}
	if (io->flag & DUP)
		dup2(io->in, io->out);
	if (io->flag & CLOSE)
		close(io->in);
}

void	doPipe(t_process_p p1, t_process_p p2)
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
	PUSH(&(((t_process_p)p1)->ioList), new_link(io_in, sizeof(*io_in)));
	PUSH(&(p2->ioList), new_link(io_out, sizeof(*io_out)));
}

int		doFork(t_process_p p, int pgid, int foreground)
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

void	doPipeline(t_job *job, t_list *pipeline)
{
	int	pid;
	while (pipeline)
	{
		if (pipeline->next)
			doPipe(pipeline->content, ((t_process_p)pipeline->content)->next);
		pid = doFork(pipeline->content, job->pgid, job->foreground);
		if (job->pgid == 0)
			job->pgid = pid;
		setpgid(pid, job->pgid);
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
	  PUT2("up");
	  if (current->type == IF)
		  current = ((current->type == IF_OR/* && last*/) || (current->type == IF_AND/* && !last*/)) ? current->right : NULL;
	  else
	  {
		  doPipeline(j, current->data);
		  current = current->right;
	  }
  }
  int foreground = 1;
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
