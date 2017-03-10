/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:03:19 by alallema          #+#    #+#             */
/*   Updated: 2017/03/10 10:58:06 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>

typedef struct	s_process
{
	struct process	*next;		/* struct list ou a changer par left right*/
	int				token;		/* token */
	char			**argv;		/* for exec */
	pid_t			pid;		/* process ID */
	char			completed;	/* true if process has completed */
	char			stopped;	/* true if process has stopped */
	int				status;		/* reported status value */
}				t_process;

/* A job is a pipeline of processes.  */
typedef struct	s_job
{
	struct job		*next;
	char			*command;		/* command line, used for messages */
	process			*first_process;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	char			notified;		/* true if user told about stopped job */
	struct termios	s_term;			/* saved terminal modes cf inc/read.h strcut s_term */
	int				*tab_fd;		// ?tab_fd[3]? int stdin, stdout, stderr;  /* standard i/o channels */
	int				flag;			/* mode exec */
	int				foreground;		/* foreground or background */
}				t_job;


/* The active jobs are linked into a list.  This is its head.   */
job *first_job = NULL;

#endif
