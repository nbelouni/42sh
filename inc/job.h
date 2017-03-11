/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:03:19 by alallema          #+#    #+#             */
/*   Updated: 2017/03/11 14:54:33 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>

//typedef struct Process Process_p;

typedef struct	s_process
{
	struct s_process	*next;		/* struct list ou a changer par left right*/
	int					token;		/* token */
	char				**cmd;		/* for exec */
	int					*tab_fd;		// ?tab_fd[3]? int stdin, stdout, stderr;  /* standard i/o channels */
	pid_t				pid;		/* process ID */
	char				completed;	/* true if process has completed */
	char				stopped;	/* true if process has stopped */
	int					status;		/* reported status value */
}				t_process;

/* A job is a pipeline of processes.  */
typedef struct	s_job
{
	struct s_job	*next;
	char			*command;		/* command line, used for messages */
	t_process		*process;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	int				notified;		/* true if user told about stopped job */
	struct termios	*s_term;			/* saved terminal modes cf inc/read.h strcut s_term */
	int				flag;			/* mode exec */
	int				foreground;		/* foreground or background */
}				t_job;


/* The active jobs are linked into a list.  This is its head.   */
//t_job *first_job = NULL;


void		export_job(t_tree *root, t_job **job_list);
t_process	*init_process(char **cmd, int token);
t_job		*init_job(int foreground);
void		process_push(t_process **begin, t_process *proc);
void		job_push(t_job **begin, t_job *job);
void		print_job(t_job *list);

#endif
