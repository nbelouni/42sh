/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:52:27 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/10 19:06:46 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define is ==
#define token(x) (x->token)


void	export_job(t_tree *root, job *job_list)
{
	t_tree *ptr;
	job	*job_iterator;

	ptr = root;
	while (ptr)
	{
		if (token(ptr) is not AMP or is not DOT)
			create_job(ptr, 0);
		else
		{
			ptr = ptr->left;
			create_job(ptr, token(AMP));
		}
		ptr = ptr->right;
	}
}

job	*create_job(t_tree *root, int foreground)
{
	t_job	*job;

	job = ft_memalloc(sizeof(t_job));
	job->foreground = foreground;
	create_process_tree(ptr, env);
}

void	 create_process_tree(t_tree *root)
{
	Node_p *process_tree;
	Node_p current_node;
	t_tree *ptr;

	ptr = root;
	*process_tree = create_node();
	current_node = *process_tree;
	while (ptr)
	{
		if (token(ptr) is AND)
			create_conditionIf(IF_AND);
		else if (token(ptr) is OR)
			;
		ptr = ptr->right;
	}
}

ConditionIf_p create_ConditonIf()
{

}

Node_p create_node()
{

}

Process_p	create_process()
{
	Process_p process;
	
	return (process);
}

void	check_tok(t_tree *node)
{
	if (token(node) is OR || token(node) is AND)
		
	/*
	if (token(node) is SR_DIR)
		ft_redir_right(node, env);
	if (token(node) is PIPE)
	ft_pipe(node, env);*/
}
