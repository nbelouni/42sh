/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:03:19 by alallema          #+#    #+#             */
/*   Updated: 2017/03/17 22:04:27 by alallema         ###   ########.fr       */
/*                                                                            */
/* ********************************************************)****************** */

#ifndef JOB_H
# define JOB_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>

#define PUSH(x, elem)	(insert_link_top(x, new_link(elem, sizeof(elem))))
#define TOP(x) (x->content)
#define POP(x)	(delete_link(remove_link_top(x)))

typedef struct s_node *t_node_p;

typedef struct	s_sh
{
	int			tty;
	int			is;
	pid_t		pgid;
}				t_sh;

typedef enum	e_type_node
{
	PROCESS,
	IF
}				t_type_node;

typedef enum	e_type_if
{
	IF_OR,
	IF_AND
}				t_type_if;

struct s_node{
	void		*data;
	size_t		size;
	t_type_node	type;
	t_node_p	left;
	t_node_p	right;
};

typedef	t_list	*List_p;
/*
typedef struct List *List_p;

struct List{
	List_p		next;
	void		*content;
	size_t		content_size;
};
*/
typedef struct s_condition_if *t_condition_if_p;

struct s_condition_if{
	t_type_if type;
};

typedef struct s_process *t_process_p;

typedef struct s_process
{
//	t_process_p		next;		/* struct list ou a changer par left right*/
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
//	struct s_job	*next;
	char			*command;		/* command line, used for messages */
	t_node_p		process_tree;	/* list of processes in this job */
	pid_t			pgid;			/* process group ID */
	char			notified;		/* true if user told about stopped job */
	struct termios	s_term;			/* saved terminal modes cf inc/read.h strcut s_term */
	int				flag;			/* mode exec */
	int				foreground;		/* foreground or background */
}				t_job;

void		insert_link_top(List_p *refHeadTop, List_p subLinkChain);
void		*remove_link_top(List_p *refHeadTop);
void		*delete_link(List_p link);
void		*new_link(void *content, size_t content_size);
void		insert_link_bottom(List_p *refHeadTop, List_p subLinkChain);

t_node_p	create_process(t_tree *nodeProcess);
t_node_p	create_condition_if(t_tree *nodeConditionIf, t_node_p right_node, t_node_p left_node);
t_node_p	create_pipe(t_node_p right_node, t_node_p left_node);
t_node_p	create_redir(t_tree *nodeRedir, t_node_p left_node);

void		test_func(t_tree *root, List_p *Jobs);

t_sh		*get_sh(void);
void		init_shell(void);
void		get_sig_ign(void);
void		get_sig_dfl(void);

void		launch_job(t_list *list, t_lst *env);
void		launch_process(t_process_p p, pid_t pgid, int fd[2], int err, int f, t_lst *env);

void		ft_exec(char **s, t_lst *env);

#endif
