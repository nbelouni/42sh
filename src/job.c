/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:52:27 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/11 15:08:15 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#define is ==
#define isnot !=
#define token(x) (x->token)

void		create_process(t_tree *node, t_process **proc, int token)
{
	t_process	*new;

	PUT2("\n--create process--\n")
	new = init_process(node->cmd, token);
	process_push(proc, new);
}

void		export_process(t_tree *root, t_process **proc, int token)
{
	t_tree		*ptr;

	ptr = root;
	PUT2("\n--export process--\n")
	if (!ptr)
		return ;
	token = token(ptr);
	if (token(ptr) is CMD)
	{
		PUT2("\n--create cmd--\n")
		create_process(ptr, proc, token);
	}
	if (ptr->left)
		export_process(ptr->left, proc, token);
	if (ptr->right)
		export_process(ptr->right, proc, token);
}

void		create_job(t_tree *root, int foreground, t_job **job_list)
{
	t_job		*job;
	t_process	*proc;

	PUT2("\n--create job--\n")
	if (!root)
		return ;
	job = init_job(foreground);
	export_process(root, &proc, 0);
	job->process = proc;
	job_push(job_list, job);
}

void		export_job(t_tree *root, t_job **job_list)
{
	t_tree		*ptr;

	ptr = root;
	PUT2("\n--export job--\n")
	while (ptr)
	{
		if ((token(ptr) isnot AMP) || (token(ptr) isnot DOT))
			create_job(ptr, 0, job_list);
		else
		{
			ptr = ptr->left;
			create_job(ptr, 1, job_list);
		}
		ptr = ptr->right;
	}
}
