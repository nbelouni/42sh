/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:52:27 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/22 17:43:28 by llaffile         ###   ########.fr       */
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
	bzero(job, sizeof(*job));
	job->foreground = foreground;
	job->process_tree = create_process_tree(root);
	return (job);
}

void	export_job(t_tree *root, List_p *job_list)
{
	while (TOKEN(root) IS AMP || TOKEN(root) IS DOT)
	{
		insert_link_bottom(job_list, new_link(create_job(root->left, (TOKEN(root) IS DOT) ? 1: 0), sizeof(t_job)));
		root = root->right;
	}
	insert_link_bottom(job_list, new_link(create_job(root, 1), sizeof(t_job)));
}

t_condition_if_p new_condition_if(t_type_if type)
{
	t_condition_if_p	ptr;

	ptr = malloc(sizeof(*ptr));
	bzero(ptr, sizeof(*ptr));
	ptr->type = type;
	return (ptr);
}

t_node_p new_node(t_type_node type, size_t size)
{
	t_node_p	ptr;

	ptr = malloc(sizeof(*ptr));
	bzero(ptr, sizeof(*ptr));
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
	bzero(ptr, sizeof(*ptr));
	ptr->argv = argv;
	printf("iolist : <%p>\n", ptr->ioList);
	return (ptr);
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
	insert_link_bottom((List_p *)&(left_node->data), right_node->data);
	delete_node(right_node);
	return (left_node);
}
/* 
	Temporary code which join the redirection operator and arguments, --ABSOLUTLY NOT FINAL-- form of redirection. We are using this 
	solution just to perform some check.
*/

t_node_p create_redir(t_tree *nodeRedir, t_node_p left_node)
{
	Io_p	io;
	int		left;
	t_process_p	process;

	io = new_io();
	puts("0");
	dprintf(2, "cmd : <%p>\n", nodeRedir->right->cmd);
	io->str = (nodeRedir->right->cmd)[0];
	io->flag |= DUP;
	puts("1");
	if (!(left = atoi((nodeRedir->cmd)[0])))
		left = 1 - ((TOKEN(nodeRedir) == SL_DIR)? 1: 0);
	puts("2");
	if (TOKEN(nodeRedir) == SR_DIR || TOKEN(nodeRedir) == SL_DIR || TOKEN(nodeRedir) == DR_DIR || TOKEN(nodeRedir) == DL_DIR)
	{
		io->dup_target = left;
		io->flag |= OPEN | CLOSE;
	}
	puts("3");
	if (TOKEN(nodeRedir) == DR_DIR || TOKEN(nodeRedir) == SR_DIR)
		io->mode |= O_WRONLY;
	puts("4");
	if(TOKEN(nodeRedir) == DR_DIR)
		io->mode |= O_APPEND;
	puts("5");
	if(TOKEN(nodeRedir) == SL_DIR)
		io->mode |= O_RDONLY;
	puts("6");
	if (TOKEN(nodeRedir) == DIR_AMP)
	{
		io->dup_src = atoi((nodeRedir->right->cmd)[0]);
		io->dup_target = left;
	}
	puts("7");
	process = left_node->data;
	insert_link_bottom(&process->ioList, new_link(io, sizeof(*io)));
	return (left_node);
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

void test_func(t_tree *root)
{
	List_p Jobs = NULL;

	export_job(root, &Jobs);
	printJobList(Jobs);
}
