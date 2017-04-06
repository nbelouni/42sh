/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:45:12 by alallema          #+#    #+#             */
/*   Updated: 2017/04/06 14:57:37 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "hash.h"
#include "list.h"
#include "job.h"
#include "io.h"

/* 
	Temporary code which join the redirection operator and arguments, --ABSOLUTLY NOT FINAL-- form of redirection. We are using this 
	solution just to perform some check.
*/
static t_mode		(tab_mode[7]) = {
	[0] = { SL_DIR, O_RDONLY, OPEN | CLOSE},
	[1] = { SR_DIR, O_WRONLY | O_CREAT | O_TRUNC, OPEN | CLOSE},
	[2] = { DL_DIR, 0, CLOSE | WRITE},
	[3] = { DR_DIR, O_WRONLY | O_APPEND | O_CREAT, OPEN | CLOSE},
	[4] = { LR_DIR, O_RDWR | O_CREAT, OPEN | CLOSE},
	[5] = { DIR_L_AMP, O_RDWR, 0},
	[6] = { DIR_R_AMP, O_RDWR, 0},
};

void		set_mode_redir(t_tree *nodeRedir, t_io *io, int left)
{
	int				i;

	i = 0;
	while (i < 7)
	{
		if (tab_mode[i].redir == TOKEN(nodeRedir))
		{
			io->flag |= tab_mode[i].flag;
			io->mode = tab_mode[i].mode;
			if ((i == 5 || i == 6) && (nodeRedir->right->cmd)[0][0] == '-')
			{
				io->flag |= CLOSE;
				io->dup_src = left;
			}
			else if (i == 5 || i == 6)
				io->dup_src = atoi((nodeRedir->right->cmd)[0]);
		}
		i++;
	}
}

t_io		*iter_retur_prev(t_list *list, void *(f)(void *))
{
	t_list	*prev;

	prev = list;
	while (list)
	{
		f(list->content);
		list = list->next;
	}
	if (prev)
		return (prev->content);
	return (NULL);
}

void		restore_fd(t_io *io)
{
	if (!io)
		return ;
//	PUT2("io->tab_fd[0]\n");
//	E(io->tab_fd[0]);X('\n');
//	PUT2("io->tab_fd[1]\n");
//	E(io->tab_fd[1]);X('\n');
//	PUT2("io->str\n");
//	PUT2(io->str);X('\n');
	if (io->tab_fd[0] !=-1)
	{
		dup2(io->tab_fd[0], io->dup_target);
		close(io->tab_fd[0]);
	}
	if (io->tab_fd[1] !=-1)
	{
		dup2(io->tab_fd[1], io->dup_src);
		close(io->tab_fd[1]);
	}
}

void		save_fd(t_io *io, int type_redir)
{
	(void)type_redir;
//	PUT2("io->dup_src\n");
//	E(io->dup_src);X('\n');
//	PUT2("io->dup_target\n");
//	E(io->dup_target);X('\n');
	io->tab_fd[0] = dup(io->dup_target);
	if (type_redir == DIR_L_AMP || type_redir == DIR_R_AMP)
		io->tab_fd[1] = dup(io->dup_src);
}

t_node_p	create_redir(t_tree *nodeRedir, t_node_p left_node)
{
	t_io			*io;
	int				left;
	t_process_p		process;

	io = new_io();
	io->str = (nodeRedir->right->cmd)[0];
	io->flag = DUP;
	if (!nodeRedir->cmd)
		left = ((TOKEN(nodeRedir) == SL_DIR || TOKEN(nodeRedir) == LR_DIR ||
		TOKEN(nodeRedir) == DIR_L_AMP || TOKEN(nodeRedir) == DL_DIR) ? 0: 1);
	else
		left = atoi((nodeRedir->cmd)[0]);
	io->dup_target = left;
	set_mode_redir(nodeRedir, io, left);
	save_fd(io, TOKEN(nodeRedir));
	process = ((t_list *)left_node->data)->content;
	insert_link_bottom(&(process->ioList), new_link(io, sizeof(*io)));
	return (left_node);
}
