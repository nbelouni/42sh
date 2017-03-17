/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:52:27 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/17 22:13:13 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

#define IS ==
#define TOKEN(x) (((t_tree *)x)->token)
#define isCondition(x) (x == OR || x == AND)
#define isRedir(x) (x == DIR_AMP || x == SR_DIR || x == SL_DIR || x == DR_DIR || x == DL_DIR)

void	list_iter(List_p list, void (f)(void *));

void	print_stack(t_tree *elem)
{
	printf("\tToken : <%d>\n", elem->token);
}

int	iter_post_ord(t_tree **ptr, List_p *stock)
{
	while (*ptr)
	{
//		puts("Bottom");
		if ((*ptr)->right)
			PUSH(stock, (*ptr)->right);
		PUSH(stock, *ptr);
		*ptr = (*ptr)->left;
	}
/*	printf("=--Stack-1-=\n");
	list_iter(*stock, (void *)&print_stack);*/
	*ptr = POP(stock);
	if (*stock && (*ptr)->right && TOP((*stock)) == (*ptr)->right)
	{
		POP(stock);
		PUSH(stock, *ptr);
		*ptr = (*ptr)->right;
/*		printf("=--Stack-B-=\n");
		list_iter(*stock, (void *)&print_stack);*/
		return (0);
	}
	return (1);
//	return (POP(stock));
}

t_node_p	create_process_tree(t_tree *root)
{
	List_p	stack;
	List_p	stock;

	stock = NULL;
	stack = NULL;
	while (true)
	{
		if (iter_post_ord(&root, &stock))
		{
/*			printf("=--Stack--=\n");
			list_iter(stock, (void *)&print_stack);*/
			if (TOKEN(root) IS CMD)
				PUSH(&stack, create_process(root));
			else if (isCondition(TOKEN(root)))
				PUSH(&stack, create_condition_if(root, POP(&stack), POP(&stack)));//Condition, right_node, left_node
			else if (TOKEN(root) IS PIPE)
				PUSH(&stack, create_pipe(POP(&stack), POP(&stack)));//right_node, left_node
			else if (isRedir(TOKEN(root)))
				PUSH(&stack, create_redir(root, POP(&stack)));//Redir, targetNode, left_node
			root = NULL;
		}
		if (!stock)
			break;
	}
	return (POP(&stack));
}

t_job	*create_job(t_tree *root, int foreground)
{
	t_job	*job;

	job = ft_memalloc(sizeof(t_job));
	job->foreground = foreground;
	job->process_tree = create_process_tree(root);
	return (job);
}

void	export_job(t_tree *root, List_p *job_list)
{
	while (root && (TOKEN(root) IS AMP || TOKEN(root) IS DOT))
	{
		insert_link_bottom(job_list, new_link(create_job(root->left, (TOKEN(root) IS DOT) ? 1: 0), sizeof(t_job)));
		root = root->right;
	}
	if (root)
		insert_link_bottom(job_list, new_link(create_job(root, 1), sizeof(t_job)));
}

t_condition_if_p new_condition_if(t_type_if type)
{
	t_condition_if_p	ptr;

	ptr = malloc(sizeof(*ptr));
	ptr->type = type;
	return (ptr);
}

t_node_p new_node(t_type_node type, size_t size)
{
	t_node_p	ptr;

	ptr = malloc(sizeof(*ptr));
	ptr->type = type;
	ptr->size = size;
	return (ptr);
}

void	delete_node(t_node_p node)
{
	free(node);
}

t_process_p	new_process(char **argv)
{
	t_process_p ptr;

	ptr = malloc(sizeof(*ptr));
	ptr->argv = argv;
	return (ptr);
}

void	*new_link(void *content, size_t content_size)
{
	List_p	link;

	link = malloc(sizeof(*link));
	bzero(link, sizeof(*link));
	link->content = content;
	link->content_size = content_size;
	return (link);
}

void	*delete_link(List_p link)
{
	void	*content;

	content = link->content;
	free(link);
	return (content);
}

void	*remove_link_top(List_p *refHeadTop)
{
	List_p	link;

	link = *refHeadTop;
	(*refHeadTop) = (*refHeadTop)->next;
	link->next = NULL;
	return (link);
}

void	insert_link_top(List_p *refHeadTop, List_p subLinkChain)
{
	List_p	link;

	link = subLinkChain;
	while (link->next)
		link = link->next;
	link->next = *refHeadTop;
	*refHeadTop = subLinkChain;
}

void	insert_link_bottom(List_p *refHeadTop, List_p subLinkChain)
{
	while (*refHeadTop)
		refHeadTop = &(*refHeadTop)->next;
	*refHeadTop = subLinkChain;
}

t_node_p	create_process(t_tree *nodeProcess)
{
	t_node_p ptr;

	ptr = new_node(PROCESS, sizeof(struct s_process));
	ptr->data = new_link(new_process(nodeProcess->cmd), sizeof(struct s_node));
	return (ptr);
}

t_node_p	create_condition_if(t_tree *nodeConditionIf, t_node_p right_node, t_node_p left_node)
{
	t_node_p ptr;

	ptr = new_node(IF, sizeof(struct s_condition_if));
	ptr->left = left_node;
	ptr->right = right_node;
	ptr->data = new_condition_if((TOKEN(nodeConditionIf) IS OR)? IF_OR : IF_AND);
	return (ptr);
}

t_node_p	create_pipe(t_node_p right_node, t_node_p left_node)
{
	insert_link_bottom(&((List_p)left_node->data)->next, right_node->data);
	delete_node(right_node);
	return (left_node);
}
/* 
	Temporary code which join the redirection operator and arguments, --ABSOLUTLY NOT FINAL-- form of redirection. We are using this 
	solution just to perform some check.
*/

t_node_p create_redir(t_tree *nodeRedir, t_node_p left_node)
{
	t_process_p	process;
	char		*redir_opt_string;
	char		*redir_arg_string;
	size_t		size_redir_string;

	redir_opt_string = (nodeRedir->cmd)[0];
	redir_arg_string = (nodeRedir->right->cmd)[0];
	size_redir_string = strlen(redir_opt_string) + strlen(redir_arg_string) + 1;
	process = left_node->data;
	process->temp_redir = malloc(size_redir_string);
	strcat(process->temp_redir, redir_opt_string);
	strcat(process->temp_redir, redir_arg_string);
	return (left_node);
}

void	list_iter(List_p list, void (f)(void *))
{
	while (list)
	{
		f(list->content);
		list = list->next;
	}
}

void spacer(int io)
{
	static int depth;
	
	for (int i = 0; io >0 && i < depth ; i++)
	{
		putchar('|');
		putchar(' ');
	}
	depth += io;
}

void printProcess(t_process_p process)
{
	spacer(1);
	printf("[PROCESS]\t");
	printf("command : <%s>\t", (process->argv)[0]);
	for (int i = 1; (process->argv)[i];  i++)
		printf("A%d: <%s>\t", i, (process->argv)[i]);
	printf("self: <%p>\t\n", &process);
	spacer(-1);
}

void printConditionIf(t_condition_if_p condition)
{
	spacer(1);
	printf("[CONDITION]\t");
	printf("if : <%s>\t", (condition->type == IF_OR)? "OR": "AND");
	printf("self: <%p>\t\n", &condition);
	spacer(-1);
}


void printProcessList(List_p processList)
{
	list_iter(processList, (void *)&printProcess);
}

void printNode(t_node_p processTree)
{
	spacer(1);
	printf("[NODE]\n");
	if (processTree->type IS PROCESS)
		printProcessList(processTree->data);
	else
	{
		printConditionIf(processTree->data);
		printNode(processTree->left);
		printNode(processTree->right);
	}
	spacer(-1);
}

void printJob(t_job *job)
{
	spacer(1);
	printf("[JOB]\t");
	printf("Command : <%s>\t", job->command);
	printf("Foreground : <%d>\t\n", job->foreground);
	printNode(job->process_tree);
	spacer(-1);
}

void printJobList(List_p jobList)
{
	list_iter(jobList, (void *)&printJob);
}

void test_func(t_tree *root, List_p *Jobs)
{
//	List_p Jobs = NULL;

//	export_job(root, &Jobs);
	export_job(root, Jobs);
//	printJobList(*Jobs);
}
