/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:15:02 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/22 18:38:34 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

//job *find_job (pid_t pgid)
//{
//  job *j;
//
//  for (j = first_job; j; j = j->next)
//    if (j->pgid == pgid)
//      return j;
//  return NULL;
//}
//
///* Return true if all processes in the job have stopped or completed.  */
//int	job_is_stopped (job *j)
//{
//  process *p;
//
//  for (p = j->first_process; p; p = p->next)
//    if (!p->completed && !p->stopped)
//      return 0;
//  return 1;
//}
//
///* Return true if all processes in the job have completed.  */
//int	job_is_completed (job *j)
//{
//  process *p;
//
//  for (p = j->first_process; p; p = p->next)
//    if (!p->completed)
//      return 0;
//  return 1;
//}
//
///* Store the status of the process pid that was returned by waitpid.
//   Return 0 if all went well, nonzero otherwise.  */
//
//int	mark_process_status(pid_t pid, int status)
//{
//  job *j;
//  process *p;
//
//  if (pid > 0)
//    {
//      for (j = first_job; j; j = j->next)
//        for (p = j->first_process; p; p = p->next)
//          if (p->pid == pid)
//            {
//              p->status = status;
//              if (WIFSTOPPED (status))
//                p->stopped = 1;
//              else
//                {
//                  p->completed = 1;
//                  if (WIFSIGNALED (status))
//                    fprintf (stderr, "%d: Terminated by signal %d.\n",
//                             (int) pid, WTERMSIG (p->status));
//                }
//              return 0;
//             }
//      fprintf (stderr, "No child process %d.\n", pid);
//      return -1;
//    }
//  else if (pid == 0 || errno == ECHILD)
//    return -1;
//  else {
//    perror ("waitpid");
//    return -1;
//  }
//}
//
///* Check for processes that have status information available,
//   without blocking.  */
//
//void	update_status(void)
//{
//  int status;
//  pid_t pid;
//
//  do
//    pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
//  while (!mark_process_status (pid, status));
//}
//
///* Check for processes that have status information available,
//   blocking until all processes in the given job have reported.  */
//
//void	wait_for_job (job *j)
//{
//  int status;
//  pid_t pid;
//
//  do
//    pid = waitpid (WAIT_ANY, &status, WUNTRACED);
//  while (!mark_process_status (pid, status)
//         && !job_is_stopped (j)
//         && !job_is_completed (j));
//}
//
///* Format information about job status for the user to look at.  */
//
//void	format_job_info(job *j, const char *status)
//{
//  fprintf (stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
//}
//
///* Notify the user about stopped or terminated jobs.
//   Delete terminated jobs from the active job list.  */
//
//void do_job_notification (void)
//{
//  job *j, *jlast, *jnext;
//  process *p;
//
//  update_status ();
//  jlast = NULL;
//  for (j = first_job; j; j = jnext)
//    {
//      jnext = j->next;
//      if (job_is_completed (j)) {
//        format_job_info (j, "completed");
//        if (jlast)
//          jlast->next = jnext;
//        else
//          first_job = jnext;
//        free_job (j);
//      }
//      else if (job_is_stopped (j) && !j->notified) {
//        format_job_info (j, "stopped");
//        j->notified = 1;
//        jlast = j;
//      }
//      else
//        jlast = j;
//    }
//}

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
		if (ptr)
		{
			PUSH(stock, ptr);
			ptr = ptr->left;
		}
		else
		{
			return (POP(stock));
		}
	}
	return (NULL);
}

void	doRedir(Io_p io)
{
	puts("doRedir");
	dprintf(2,"flags : <%d> and <%p>\n", io->flag, io);
	if (io->flag & OPEN)
	{
		dprintf(2,"open <%p>\n", io);
		if (access(io->str, X_OK) == -1)
			io->mode |= O_CREAT;
		io->dup_src = open(io->str, io->mode);
	}
	if (io->flag & DUP)
	{
		dprintf(2,"dup <%p>\n", io);
		int rd = dup2(io->dup_src, io->dup_target);
		dprintf(2,"rd : <%d> && in : <%d><%p>\n", rd, io->dup_src, io);
	}
	if (io->flag & CLOSE)
	{
		dprintf(2,"close <%p>\n", io);
		close(io->dup_src);
	}
}

int	doPipe(t_process_p p1, t_process_p p2)
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
	io_in->flag = DUP | CLOSE;
	io_out->flag = DUP | CLOSE;

	/* in| */
	io_in->dup_src = ioPipe[1]; // dup2(in, STDOUT_FILENO)
	io_in->dup_target = STDOUT_FILENO;

	/* |out */
	io_out->dup_src = ioPipe[0]; // dup2(in, STDIN_FILENO)
	io_out->dup_target = STDIN_FILENO;
	
	dprintf(2,"flags : <%d> and i<%p>\n", io_in->flag, io_in);
	dprintf(2,"flags : <%d> and o<%p>\n", io_out->flag, io_out);
	PUSH(&(p1->ioList), io_in);
	PUSH(&(p2->ioList), io_out);
	return (ioPipe[1]);
}

int		doFork(t_process_p p, int pgid, int foreground)
{
	int	pid;
	
	pid = fork ();
	if (pid == 0)
		launch_process(p, pgid, foreground);
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
	t_process_p	p;
	int pp;
	
	while (pipeline)
	{
		p = (t_process_p)pipeline->content;
		dprintf(2,"iol : <%p>\n", p->ioList);
		if (pipeline->next)
			pp = doPipe(pipeline->content, pipeline->next->content);
		pid = doFork(pipeline->content, job->pgid, job->foreground);
		if (job->pgid == 0)
			job->pgid = pid;
		setpgid(pid, job->pgid);
		pipeline = pipeline->next;
		close(pp);
	}
}

void	launch_job(t_job *j)
{
  t_node_p	current;
  List_p	stack;

  current = j->process_tree;
  stack = NULL;
  while ((current = iterInOrder(current, &stack)))
  {
	  PUT2("in\n");
	  if (current->type == IF)
		  current = ((current->type == IF_OR/* && last*/) || (current->type == IF_AND/* && !last*/)) ? current->right : NULL;
	  else
	  {
	  	PUT2("out\n");
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
