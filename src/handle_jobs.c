/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:15:02 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/23 20:41:37 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void	sigchldhandler(int sig)
{
	(void)sig;
	dprintf(2, "in handler\n");
	
}

void print_process(t_process_p process)
{
	dprintf(2, "[PROCESS]\n");
	dprintf(2, "\tself: <%p>\n", &process);
	dprintf(2, "\tpid: <%d>\n", process->pid);
	dprintf(2, "\tcompleted: <%d>\tstopped: <%d>\tstatus: <%d>\n", process->completed, process->stopped, process->status);
}

void print_job(t_job *job)
{
	dprintf(2, "[JOB]\n");
	dprintf(2, "\tCommand : <%s>\n", job->command);
	dprintf(2, "\tForeground : <%d>\t pgid : <%d>\t notified : <%d>\n", job->foreground, job->pgid, job->notified);
}

extern	List_p	jobList;
int last = 0;

t_job *find_job(pid_t pgid)
{
  t_job		*j;
  List_p	ptr;

  ptr = jobList;
  while (ptr)
  {
	  j = ptr->content;
	  if (j->pgid == pgid)
		  return (j);
	  ptr = ptr->next;
  }
  return (NULL);
}

/* Return true if all processes in the job have stopped or completed.  */
int	job_is_stopped (t_job *j)
{
  t_process_p p;
  List_p	ptr;

  ptr = j->waitProcessList;
  fputs("is stopped\n", stderr);
  print_job(j);
  while (ptr)
  {
	  p = ptr->content;
	  fputs("is stopped\n", stderr);
	  print_process(p);
	  if (!p->completed && !p->stopped)
		  return 0;
	  ptr = ptr->next;
  }
  return 1;
}

/* Return true if all processes in the job have completed.  */
int	job_is_completed(t_job *j)
{
  t_process_p p;
  List_p	ptr;

  ptr = j->waitProcessList;
  fputs("is complete\n", stderr);
  print_job(j);
  while (ptr)
  {
	  p = ptr->content;
	  fputs("is complete\n", stderr);
	  print_process(p);
	  if (!p->completed)
		  return 0;
	  ptr = ptr->next;
  }
  return 1;
}

/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */

t_process_p	getProcessByPid(pid_t pid)
{
	List_p	ptrJob;
	List_p	ptrProcess;
	t_job		*j;
	t_process_p	p;

	ptrJob = jobList;
	fputs("in getbyid\n", stderr);
	while (ptrJob)
	{
		j = ptrJob->content;
		print_job(j);
		ptrProcess = j->waitProcessList;
		while (ptrProcess)
		{
			p = ptrProcess->content;
			print_process(p);
			if (p->pid == pid)
			{
				fputs("mid getbyid\n", stderr);
				return (p);
			}
			ptrProcess = ptrProcess->next;
		}
		ptrJob = ptrJob->next;
	}
	fputs("bot getbyid\n", stderr);
	return (NULL);
}

int	mark_process_status(pid_t pid, int status)
{
  t_process_p p;

  fputs("Inside\n", stderr);
  if (pid > 0)
  {
	  fputs("up\n", stderr);
	  if ((p = getProcessByPid(pid)))
	  {
		  p->status = status;
		  if (WIFSTOPPED(status))
			  p->stopped = 1;
		  else
		  {
			  p->completed = 1;
			  last = WEXITSTATUS(status);
			  if (WIFSIGNALED (status))
				  fprintf (stderr, "%d: Terminated by signal %d.\n",
						   (int) pid, WTERMSIG (p->status));
		  }
		  printf("in\n");
		  print_process(p);
		  return 0;		
	  }
	  else
		  return (fprintf (stderr, "No child process %d.\n", pid), -1);
  }
  else if (pid == 0 || errno == ECHILD)
  {
	  fputs("outside\n", stderr);
	  return -1;
  }
  else
  {
	  fputs("bot\n", stderr);
	  return (perror("waitpid"), -1);
  }
}

/* Check for processes that have status information available,
   without blocking.  */

void	update_status(void)
{
  int status;
  pid_t pid;

  fputs("update status\n", stderr);
  while (true)
  {
    pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
	if (mark_process_status(pid, status))
		break ;
  }
}

/* Check for processes that have status information available,
   blocking until all processes in the given job have reported.  */

void	wait_for_job(t_job *j)
{
  int status;
  pid_t pid;

  print_job(j);
  perror("--wait4Job--");
  errno = 0;
  signal(SIGCHLD, SIG_DFL);
  signal(SIGCHLD, chld_handler);
  if (errno)
	  perror("signal");
  while (true)
  {
	  dprintf(2, "Waiting ...\n");
	  pid = waitpid(-1, &status, WUNTRACED);// | WNOHANG);
	  dprintf(2, "Continuing <%d> <%s>\n", getpid(), strerror(errno));
	  perror("--waitpid--");
	  if (mark_process_status(pid, status) || job_is_stopped(j) || job_is_completed(j))
		  break ;
  }
}

/* Format information about job status for the user to look at.  */

void	format_job_info(t_job *j, const char *status)
{
  fprintf(stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */

void	delete_job(t_job * j)
{
	(void)j;
}

void do_job_notification(void)
{
	t_job *j;
	List_p	*ptr;
	
	update_status();
	ptr = &jobList;
	while (*ptr)
	{
		fputs("job_notif\n", stderr);
		j = (*ptr)->content;
		if (job_is_completed(j))
		{
			format_job_info (j, "completed");
			delete_job(POP(ptr));
			printf("<%p> and *<%p>\n", ptr, *ptr);
		}
		else if (job_is_stopped(j) && !j->notified)
		{
			format_job_info(j, "stopped");
			j->notified = 1;
		}
		if (*ptr)
			ptr = &(*ptr)->next;
	}
}

static void		put_job_in_background(t_job *j, int cont)
{
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
}

static void		put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp (g_sh_tty, j->pgid);
	perror("put_job_in_foreground");
	if (cont)
	{
//		tcsetattr (g_sh_tty, TCSADRAIN, &j->tmodes);
		if (kill(- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
	}
	wait_for_job (j);
	tcsetpgrp (g_sh_tty, g_sh_pgid);

//	tcgetattr (g_sh_tty, &j->tmodes);
//	tcsetattr (g_sh_tty, TCSADRAIN, &shell_tmodes);
}

void	mark_job_as_running (t_job *j)
{
  t_process_p	p;
  List_p	ptr;

  ptr = j->waitProcessList;
  while (ptr)
  {
	  p = ptr->content;
	  p->stopped = 0;
	  ptr = ptr->next;
  }
  j->notified = 0;
}

/* Continue the job J.  */

void	continue_job (t_job *j, int foreground)
{
  mark_job_as_running (j);
  if (foreground)
    put_job_in_foreground (j, 1);
  else
    put_job_in_background (j, 1);
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
  print_process(process);
//  sleep(10);
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
	fputs("doRedir\n", stderr);
	if (io->flag & OPEN)
	{
//		dprintf(2,"open <%p>\n", io);
		if (access(io->str, X_OK) == -1)
			io->mode |= O_CREAT;
		io->dup_src = open(io->str, io->mode, DEF_FILE);
	}
	if (io->flag & DUP)
	{
//		dprintf(2,"dup <%p>\n", io);
		dup2(io->dup_src, io->dup_target);
//		dprintf(2,"rd : <%d> && in : <%d><%p>\n", rd, io->dup_src, io);
	}
	if (io->flag & CLOSE)
	{
//		dprintf(2,"close <%p>\n", io);
		close(io->dup_src);
	}
}

int	doPipe(t_process_p p1, t_process_p p2, 	int	*io_pipe)
{
	Io_p	io_in;
	Io_p	io_out;

	if (pipe(io_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	io_in = new_io();
	io_out = new_io();
	io_in->flag = DUP | CLOSE;
	io_out->flag = DUP | CLOSE;
	io_in->dup_src = io_pipe[1];
	io_in->dup_target = STDOUT_FILENO;
	io_out->dup_src = io_pipe[0];
	io_out->dup_target = STDIN_FILENO;
	PUSH(&(p1->ioList), io_in);
	PUSH(&(p2->ioList), io_out);
	return (io_pipe[1]);
}

int		doFork(t_process_p p, int pgid, int foreground)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		launch_process(p, pgid, foreground);
		exit(0);
	}
	else if (pid < 0)
	{
		perror ("fork");
		exit (1);
	}
	else
	{
		p->pid = pid;
		return (pid);
	}
}

void	doPipeline(t_job *job, t_list *pipeline)
{
	int			pid;
	int			io_pipe[2];
	int			in;
	int			out;

	in = STDIN_FILENO;
	while (pipeline)
	{
		out = (pipeline->next)? doPipe(pipeline->content, pipeline->next->content, io_pipe): STDOUT_FILENO;
		pid = doFork(pipeline->content, job->pgid, job->foreground);
		if (job->pgid == 0)
			job->pgid = pid;
		setpgid(pid, job->pgid);
		insert_link_bottom(&job->waitProcessList, new_link(pipeline->content, pipeline->content_size));
		pipeline = pipeline->next;
		if (out != STDOUT_FILENO)
			close(out);
		if (in != STDIN_FILENO)
			close(in);
		in = io_pipe[0];	
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
		printf("last : <%d>\n", last);
		if (current->type == IF)
		 	current = ((((t_condition_if_p)current->data)->type == IF_OR && last) || (((t_condition_if_p)current->data)->type == IF_AND && !last)) ? current->right : NULL;
		else
		{
			doPipeline(j, current->data);
			current = current->right;
		}
	}
	insert_link_bottom(&jobList, new_link(j, sizeof(*j)));
  if (j->foreground)
	put_job_in_foreground(j, 0);
 else
  put_job_in_background(j, 0);

  do_job_notification();

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
