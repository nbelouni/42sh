/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:03:19 by alallema          #+#    #+#             */
/*   Updated: 2017/03/10 18:55:45 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>

typedef struct Node *Node_p;

enum typeNode
{
	PROCESS,
	IF
};

enum	typeIf
{
	IF_OR,
	IF_AND
};

struct Node{
	void *data;
	size_t	size;
	typeNode	type;
	Node_p left;
	Node_p right;
};

typedef struct ConditionIf *ConditionIf_p;

struct Condition

{
	typeIf type;
}
	typedef struct Process *Process_p;
	
typedef struct	Process
{
	struct Process_p	next;		/* struct list ou a changer par left right*/
	int				token;		/* token */
	char			**argv;		/* for exec */
	int				*tab_fd;		// ?tab_fd[3]? int stdin, stdout, stderr;  /* standard i/o channels */
	pid_t			pid;		/* process ID */
	char			completed;	/* true if process has completed */
	char			stopped;	/* true if process has stopped */
	int				status;		/* reported status value */
}				Process;

/* A job is a pipeline of processes.  */
typedef struct	s_job
{
	struct job		*next;
	char			*command;		/* command line, used for messages */
	Node_p			*process_tree;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	char			notified;		/* true if user told about stopped job */
	struct termios	s_term;			/* saved terminal modes cf inc/read.h strcut s_term */
	int				flag;			/* mode exec */
	int				foreground;		/* foreground or background */
}				t_job;


/* The active jobs are linked into a list.  This is its head.   */
job *first_job = NULL;

#endif
