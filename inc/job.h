/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:03:19 by alallema          #+#    #+#             */
/*   Updated: 2017/03/15 16:47:08 by alallema         ###   ########.fr       */
/*                                                                            */
/* ********************************************************)****************** */

#ifndef JOB_H
# define JOB_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>

#define push(x, elem)	(insertLinkTop(x, newLink(elem, sizeof(elem))))
#define top(x) (x->data)
#define pop(x)	(deleteLink(removeLinkTop(x)))

typedef struct Node *Node_p;

typedef enum	typeNode
{
	PROCESS,
	IF
}				typeNode;

typedef enum	typeIf
{
	IF_OR,
	IF_AND
}				typeIf;

struct Node{
	void *data;
	size_t	size;
	typeNode	type;
	Node_p left;
	Node_p right;
};

typedef struct List *List_p;

struct List{
	List_p	next;
	void	*data;
	size_t	size;
};

typedef struct ConditionIf *ConditionIf_p;

struct ConditionIf{
	typeIf type;
};

typedef struct Process *Process_p;
	
typedef struct Process
{
	Process_p		next;		/* struct list ou a changer par left right*/
	int				token;		/* token */
	char			**argv;		/* for exec */
	int				*tab_fd;		// ?tab_fd[3]? int stdin, stdout, stderr;  /* standard i/o channels */
	char			*temp_redir;
	pid_t			pid;		/* process ID */
	char			completed;	/* true if process has completed */
	char			stopped;	/* true if process has stopped */
	int				status;		/* reported status value */
}				Process;

/* A job is a pipeline of processes.  */
typedef struct	s_job
{
	struct s_job	*next;
	char			*command;		/* command line, used for messages */
	Node_p			process_tree;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	char			notified;		/* true if user told about stopped job */
	struct termios	s_term;			/* saved terminal modes cf inc/read.h strcut s_term */
	int				flag;			/* mode exec */
	int				foreground;		/* foreground or background */
}				t_job;

void	insertLinkTop(List_p *refHeadTop, List_p subLinkChain);
void	*removeLinkTop(List_p *refHeadTop);
void	*deleteLink(List_p link);
void	*newLink(void *data, size_t size);
void	insertLinkBottom(List_p *refHeadTop, List_p subLinkChain);

Node_p	createProcess(t_tree *nodeProcess);
Node_p	createConditionIf(t_tree *nodeConditionIf, Node_p rightNode, Node_p leftNode);
Node_p	createPipe(Node_p rightNode, Node_p leftNode);
Node_p	createRedir(t_tree *nodeRedir, Node_p leftNode);

#endif
