/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:52:27 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/10 21:14:18 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "hash.h"
#include "list.h"
#include "io.h"

void	print_stack(t_tree *elem)
{
	printf("\tToken : <%d>\n", elem->token);
}

int	iter_post_ord(t_tree **ptr, t_list **stock)
{
	while (*ptr)
	{
		if ((*ptr)->right)
			PUSH(stock, (*ptr)->right);
		PUSH(stock, *ptr);
		*ptr = (*ptr)->left;
	}
	*ptr = POP(stock);
	if (*stock && (*ptr)->right && TOP((*stock)) == (*ptr)->right)
	{
		POP(stock);
		PUSH(stock, *ptr);
		*ptr = (*ptr)->right;
		return (0);
	}
	return (1);
}

t_node_p	create_process_tree(t_tree *root)
{
	t_list	*stack;
	t_list	*stock;

	stock = NULL;
	stack = NULL;
	while (true)
	{
		if (iter_post_ord(&root, &stock))
		{
			if (TOKEN(root) == CMD)
				PUSH(&stack, create_process(root));
			else if ((TOKEN(root)) == OR || (TOKEN(root)) == AND)
				PUSH(&stack, create_condition_if(root, POP(&stack),
					POP(&stack)));//Condition, right_node, left_node
			else if (TOKEN(root) == PIPE)
				PUSH(&stack, create_pipe(POP(&stack), POP(&stack)));//right_node, left_node
			else if (is_dir_type(TOKEN(root)))
				PUSH(&stack, create_redir(root, POP(&stack)));//Redir, targetNode, left_node
			root = NULL;
		}
		if (!stock)
			break ;
	}
	return (POP(&stack));
}

t_job	*create_job(t_tree *root, int foreground)
{
	t_job	*job;

	job = ft_memalloc(sizeof(t_job));
	bzero(job, sizeof(*job));
	job->foreground = foreground;
	job->process_tree = create_process_tree(root);
	job->command = iter_cmd(job->process_tree);
	return (job);
}

void	export_job(t_tree *root, t_list **job_list)
{
	t_job	*j;

	while (root && (TOKEN(root) == AMP || TOKEN(root) == DOT))
	{
		insert_link_bottom(job_list, new_link(create_job(root->left,
			(TOKEN(root) == DOT) ? 1 : 0), sizeof(t_job)));
		root = root->right;
	}
	if (root)
		insert_link_bottom(job_list, new_link(create_job(root, 1), sizeof(t_job)));
	j = TOP((*job_list));
	dprintf(2, "%s : j :: <%p> && PTree :: <%p>\n", __func__, j, j->process_tree);
}

t_condition_if_p		new_condition_if(t_type_if type)
{
	t_condition_if_p	ptr;

	ptr = malloc(sizeof(*ptr));
	bzero(ptr, sizeof(*ptr));
	ptr->type = type;
	return (ptr);
}

t_node_p		new_node(t_type_node type, size_t size)
{
	t_node_p	ptr;

	ptr = malloc(sizeof(*ptr));
	bzero(ptr, sizeof(*ptr));
	ptr->type = type;
	ptr->size = size;
	return (ptr);
}

void	*delete_node(t_node_p node)
{
	void	*data;

	data = node->data;
	free(node);
	return (data);
}

t_process_p	new_process(char **argv)
{
	t_process_p ptr;

	ptr = malloc(sizeof(*ptr));
	bzero(ptr, sizeof(*ptr));
	ptr->argv = argv;
	if (is_builtin(argv))
		ptr->flag |= BUILTIN;
	return (ptr);
}

int			is_builtin(char **args)
{
	if (args != NULL && args[0] != NULL)
	{
		if (!ft_strcmp(args[0], "exit"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "env"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "setenv"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "unsetenv"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "echo"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "cd"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "fg"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "jobs"))
			return (TRUE);
		else if (!ft_strcmp(args[0], "bg"))
			return (TRUE);
	}
	return (FALSE);
}

t_node_p	create_process(t_tree *node_proc)
{
	t_node_p ptr;

	ptr = new_node(PROCESS, sizeof(struct s_process));
	ptr->data = new_link(new_process(node_proc->cmd), sizeof(struct s_process));
	return (ptr);
}

t_node_p	create_condition_if(t_tree *node_condition_if, t_node_p right_node, t_node_p left_node)
{
	t_node_p ptr;

	ptr = new_node(IF, sizeof(struct s_condition_if));
	ptr->left = left_node;
	ptr->right = right_node;
	ptr->data = new_condition_if((TOKEN(node_condition_if) == OR)
		? IF_OR : IF_AND);
	return (ptr);
}

t_node_p	create_pipe(t_node_p right_node, t_node_p left_node)
{
	insert_link_bottom((t_list **)&(left_node->data), right_node->data);
	delete_node(right_node);
	return (left_node);
}

void	*iter_pre_order(t_node_p node, t_list **stack)
{
	if (!node && !*stack)
		return (NULL);
	if (*stack)
		node = POP(stack);
	if (node->right)
		PUSH(stack, node->right);
	if (node->right)
		PUSH(stack, node->left);
	return (node);
}

void	delete_condition_if(t_condition_if_p condition_if)
{
	if (!condition_if)
		return ;
	free(condition_if);
}

void	delete_process(t_process_p process)
{
	if (!process)
		return ;
	if (process->io_list)
		delete_list(&(process->io_list), &free);
	free(process);
}

void	delete_process_tree_node(int type, void *data)
{
	if (!data)
		return ;
	if (type == IF)
		delete_condition_if(data);
	else
		delete_list((t_list **)&data, (void *)delete_process);
}

void	delete_tree(t_node_p summit_node, void (f)(int, void *))
{
	t_list	*stack;

	stack = NULL;
	while ((summit_node = iter_pre_order(summit_node, &stack)))
	{
		f(summit_node->type, delete_node(summit_node));
		summit_node = NULL;
	}
}

void	delete_job(t_job *j)
{
	delete_tree(j->process_tree, delete_process_tree_node);
	delete_list(&j->wait_process_list, (void *)delete_process);
	free(j);
}
