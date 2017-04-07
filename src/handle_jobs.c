/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:15:02 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/07 18:31:32 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void	delete_job(t_job *j);

void	sigchldhandler(int sig)
{
	(void)sig;
	dprintf(2, "in handler\n");
	
}

void print_process(t_process_p process)
{
	dprintf(2, "[PROCESS]\n");
	dprintf(2, "\tself: <%p>\n", process);
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
//	print_job(j);
	while (ptr)
	{
		p = ptr->content;
		//	  PUT2("process : ");E(p->stopped);X('\n');
//			  print_process(p);
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
//  print_job(j);
  while (ptr)
  {
	  p = ptr->content;
//	  print_process(p);
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
	while (ptrJob)
	{
		j = ptrJob->content;
//		print_job(j);
		ptrProcess = j->waitProcessList;
		while (ptrProcess)
		{
			p = ptrProcess->content;
//			print_process(p);
			if (p->pid == pid)
				return (p);
			ptrProcess = ptrProcess->next;
		}
		ptrJob = ptrJob->next;
	}
	return (NULL);
}

int	mark_process_status(pid_t pid, int status)
{
	t_process_p p;

	if (pid > 0)
	{
		if ((p = getProcessByPid(pid)))
		{
			p->status = status;
			if (WIFSTOPPED(status))
			{
				p->stopped = 1;
//				PUT2("STOP");
//				E(pid);
			}
			else
			{
				p->completed = 1;
				last = WEXITSTATUS(status);
				if (WIFSIGNALED (status))
					fprintf (stderr, "%d: Terminated by signal %d.\n",
							(int) pid, WTERMSIG (p->status));
			}
//					  print_process(p);
			return 0;		
		}
		else
			return (fprintf (stderr, "No child process %d.\n", pid), -1);
	}
	else if (pid == 0 || errno == ECHILD)
		return -1;
	else
		return (perror("waitpid"), -1);
}

/* Check for processes that have status information available,
   without blocking.  */

void	update_status(void)
{
	int status;
	pid_t pid;

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

//	sigdelset(core->sig_set, SIGCHLD);
//	sigprocmask(SIG_SETMASK, core->sig_set, NULL);
//	print_job(j);
	signal (SIGCHLD, SIG_DFL);
	while (true)
	{
		pid = waitpid(-1, &status, WUNTRACED);// | WNOHANG);
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

void do_job_notification(void)
{
	t_job *j;
	List_p	*ptr;
	
	update_status();
	ptr = &jobList;
	while (*ptr)
	{
		j = (*ptr)->content;
		if (job_is_completed(j))
		{
			format_job_info (j, "completed");
			delete_job(POP(ptr));
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

void	apply_redir(t_io *io);
void	restore_fd(t_io *io);

void	launch_process(t_process_p process, int dofork)
{
	list_iter(process->ioList, (void *)apply_redir);
	/*Je l'avais initialement mise ici mais je te l'ai deplace dans MakeChildren*/
//	if (sigprocmask(SIG_UNBLOCK, core->sig_set, NULL) < 0)/*ERROR a set*/
//		return ;
//	print_process(process);
	ft_check_exec(&(process->argv));
	if (dofork)
		exit(1);
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


void	apply_redir(t_io *io)
{
	int		pipefd[2];

	if (io->flag & OPEN)
	{
		if (io->flag & CLOSE && access(io->str, X_OK) == -1)
			io->dup_src = open(io->str, io->mode, DEF_FILE);
		if (io->dup_src < 0 && io->mode)
			fputs("42sh: No such file or directory (a placer dans les error)\n", stderr);
	}
	if (io->flag & WRITE)
	{
		pipe(pipefd);
		io->dup_src = pipefd[0];
		write(pipefd[1], io->str, ft_strlen(io->str));
		close(pipefd[1]);
	}
	if (io->flag & DUP)
	{
		if (fcntl(io->dup_src, F_GETFL) < 0/* && errno == EBADF (Bad file descriptor)*/)
			fputs("42sh: Bad file descriptor (a placer dans les error)\n", stderr);
		dup2(io->dup_src, io->dup_target);
	}
	if (io->flag & CLOSE && io->flag ^ WRITE)
		close(io->dup_src);
}

int	doPipe(t_process_p p1, t_process_p p2, 	int	*io_pipe)
{
	t_io	*io_in;
	t_io	*io_out;

	if (pipe(io_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
	io_in = new_io();
	io_out = new_io();
	io_in->tab_fd[0] = dup(STDOUT_FILENO);
	io_out->tab_fd[1] = dup(STDIN_FILENO);
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

void	giveTerm(int pgid, int foreground)
{
	sigset_t set;

	sigemptyset (&set);
	sigaddset (&set, SIGTTOU);
	sigaddset (&set, SIGTTIN);
	sigaddset (&set, SIGTSTP);
	sigaddset (&set, SIGCHLD);
	sigemptyset (&set);
	if (foreground)
		tcsetpgrp(g_sh_tty, pgid);
}


int		makeChildren(t_process_p p, int *pgid, int foreground)
{
	int	pid;
	int	fpid;

	pid = fork();
	if (pid == 0)
	{
//		if (sigprocmask(SIG_UNBLOCK, core->sig_set, NULL) < 0)/*ERROR a set*/
//			return ;
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
		fpid = getpid();
		if (*pgid == 0) *pgid = fpid;
		setpgid(fpid, *pgid);
		giveTerm(*pgid, foreground);
	}
	else if (pid < 0)
	{
		perror ("fork");
		exit (1);
	}
	else
	{
		p->pid = pid;
		if (*pgid == 0) *pgid = pid;
		setpgid(pid, *pgid);
	}
	return (pid);
}



void	execSimpleCommand(t_process_p p, int fg, int dofork, int *pgid)
{
//	int			pid;
//	int			fpid;

	if (dofork)
		if (makeChildren(p, pgid, fg))
			return ;
	launch_process(p, dofork);
}

int		shouldfork(t_job *j, List_p pipeline)
{
	int dofork = 0;
	t_process_p	p;

	p = pipeline->content;
	if (j->foreground == 0 || pipeline->next || !(p->flag & BUILTIN))
		dofork = 1;
	return (dofork);
}

void	doPipeline(t_job *job, t_list *pipeline)
{
	int			io_pipe[2];
	int			in;
	int			out;
	int			dofork = 0;

	in = STDIN_FILENO;
	dofork |= shouldfork(job, pipeline);
	dprintf(2, "Dofork : <%d>\n", dofork);
	while (pipeline)
	{
		out = (pipeline->next)? doPipe(pipeline->content, pipeline->next->content, io_pipe): STDOUT_FILENO;
		execSimpleCommand(pipeline->content, job->foreground, dofork, &(job->pgid));
		list_iter_int(((t_process_p)pipeline->content)->ioList, (void *)restore_fd, dofork);
		if (out != STDOUT_FILENO)
			close(out);
		if (in != STDIN_FILENO)
			close(in);
		in = io_pipe[0];
		delete_list(&(((t_process_p)pipeline->content)->ioList), &free);
		insert_link_bottom(&job->waitProcessList, new_link(memcpy(malloc(pipeline->content_size), pipeline->content, pipeline->content_size), pipeline->content_size));
		pipeline = pipeline->next;
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
