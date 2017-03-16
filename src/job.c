/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:52:27 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/16 19:58:39 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

#define is ==
#define token(x) (((t_tree *)x)->token)
#define isCondition(x) (x == OR || x == AND)
#define isRedir(x) (x == DIR_AMP || x == SR_DIR || x == SL_DIR || x == DR_DIR || x == DL_DIR)

void	listIter(List_p list, void (f)(void *));

void	printStack(t_tree *elem)
{
	printf("\tToken : <%d>\n", elem->token);
}

int	iterPostOrd(t_tree **ptr, List_p *stock)
{
	while (*ptr)
	{
		puts("Bottom");
		if ((*ptr)->right)
			push(stock, (*ptr)->right);
		push(stock, *ptr);
		*ptr = (*ptr)->left;
	}
/*	printf("=--Stack-1-=\n");
	listIter(*stock, (void *)&printStack);*/
	*ptr = pop(stock);
	if (*stock && (*ptr)->right && top((*stock)) == (*ptr)->right)
	{
		pop(stock);
		push(stock, *ptr);
		*ptr = (*ptr)->right;
/*		printf("=--Stack-B-=\n");
		listIter(*stock, (void *)&printStack);*/
		return (0);
	}
	return (1);
//	return (pop(stock));
}

Node_p	createProcessTree(t_tree *root)
{
	List_p	stack;
	List_p	stock;

	stock = NULL;
	stack = NULL;
	while (true)
	{
		if (iterPostOrd(&root, &stock))
		{
/*			printf("=--Stack--=\n");
			listIter(stock, (void *)&printStack);*/
			if (token(root) is CMD)
				push(&stack, createProcess(root));
			else if (isCondition(token(root)))
				push(&stack, createConditionIf(root, pop(&stack), pop(&stack)));//Condition, rightNode, leftNode
			else if (token(root) is PIPE)
				push(&stack, createPipe(pop(&stack), pop(&stack)));//rightNode, leftNode
			else if (isRedir(token(root)))
				push(&stack, createRedir(root, pop(&stack)));//Redir, targetNode, leftNode
			root = NULL;
		}
		if (!stock)
			break;
	}
	return (pop(&stack));
}

t_job	*createJob(t_tree *root, int foreground)
{
	t_job	*job;

	job = ft_memalloc(sizeof(t_job));
	job->foreground = foreground;
	job->process_tree = createProcessTree(root);
	return (job);
}

void	export_job(t_tree *root, List_p *job_list)
{
	while (token(root) is AMP || token(root) is DOT)
	{
		insertLinkBottom(job_list, newLink(createJob(root->left, (token(root) is DOT) ? 1: 0), sizeof(t_job)));
		root = root->right;
	}
	insertLinkBottom(job_list, newLink(createJob(root, 1), sizeof(t_job)));
}

ConditionIf_p newConditionIf(enum typeIf type)
{
	ConditionIf_p	ptr;

	ptr = malloc(sizeof(*ptr));
	ptr->type = type;
	return (ptr);
}

Node_p newNode(enum typeNode type, size_t size)
{
	Node_p	ptr;

	ptr = malloc(sizeof(*ptr));
	ptr->type = type;
	ptr->size = size;
	return (ptr);
}

void	deleteNode(Node_p node)
{
	free(node);
}

Process_p	newProcess(char **argv)
{
	Process_p ptr;

	ptr = malloc(sizeof(*ptr));
	ptr->argv = argv;
	return (ptr);
}



void	*newLink(void *data, size_t size)
{
	List_p	link;

	link = malloc(sizeof(*link));
	bzero(link, sizeof(*link));
	link->data = data;
	link->size = size;
	return (link);
}

void	*deleteLink(List_p link)
{
	void	*data;

	data = link->data;
	free(link);
	return (data);
}

void	*removeLinkTop(List_p *refHeadTop)
{
	List_p	link;

	link = *refHeadTop;
	(*refHeadTop) = (*refHeadTop)->next;
	link->next = NULL;
	return (link);
}

void	insertLinkTop(List_p *refHeadTop, List_p subLinkChain)
{
	List_p	link;

	link = subLinkChain;
	while (link->next)
		link = link->next;
	link->next = *refHeadTop;
	*refHeadTop = subLinkChain;
}

void	insertLinkBottom(List_p *refHeadTop, List_p subLinkChain)
{
	while (*refHeadTop)
		refHeadTop = &(*refHeadTop)->next;
	*refHeadTop = subLinkChain;
}

Node_p	createProcess(t_tree *nodeProcess)
{
	Node_p ptr;

	ptr = newNode(PROCESS, sizeof(struct Process));
	ptr->data = newLink(newProcess(nodeProcess->cmd), sizeof(struct Node));
	return (ptr);
}

Node_p	createConditionIf(t_tree *nodeConditionIf, Node_p rightNode, Node_p leftNode)
{
	Node_p ptr;

	ptr = newNode(IF, sizeof(struct ConditionIf));
	ptr->left = leftNode;
	ptr->right = rightNode;
	ptr->data = newConditionIf((token(nodeConditionIf) is OR)? IF_OR : IF_AND);
	return (ptr);
}

Node_p	createPipe(Node_p rightNode, Node_p leftNode)
{
	insertLinkBottom(&((List_p)leftNode->data)->next, rightNode->data);
	deleteNode(rightNode);
	return (leftNode);
}
/* 
	Temporary code which join the redirection operator and arguments, --ABSOLUTLY NOT FINAL-- form of redirection. We are using this 
	solution just to perform some check.
*/

Node_p createRedir(t_tree *nodeRedir, Node_p leftNode)
{
	Process_p	process;
	char		*redir_opt_string;
	char		*redir_arg_string;
	size_t		size_redir_string;

	redir_opt_string = (nodeRedir->cmd)[0];
	redir_arg_string = (nodeRedir->right->cmd)[0];
	size_redir_string = strlen(redir_opt_string) + strlen(redir_arg_string) + 1;
	process = leftNode->data;
	process->temp_redir = malloc(size_redir_string);
	strcat(process->temp_redir, redir_opt_string);
	strcat(process->temp_redir, redir_arg_string);
	return (leftNode);
}

void	listIter(List_p list, void (f)(void *))
{
	while (list)
	{
		f(list->data);
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

void printProcess(Process_p process)
{
	spacer(1);
	printf("[PROCESS]\t");
	printf("command : <%s>\t", (process->argv)[0]);
	for (int i = 1; (process->argv)[i];  i++)
		printf("A%d: <%s>\t", i, (process->argv)[i]);
	printf("self: <%p>\t\n", &process);
	spacer(-1);
}

void printConditionIf(ConditionIf_p condition)
{
	spacer(1);
	printf("[CONDITION]\t");
	printf("if : <%s>\t", (condition->type == IF_OR)? "OR": "AND");
	printf("self: <%p>\t\n", &condition);
	spacer(-1);
}


void printProcessList(List_p processList)
{
	listIter(processList, (void *)&printProcess);
}

void printNode(Node_p processTree)
{
	spacer(1);
	printf("[NODE]\n");
	if (processTree->type is PROCESS)
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
	listIter(jobList, (void *)&printJob);
}

void test_func(t_tree *root)
{
	List_p Jobs = NULL;

	export_job(root, &Jobs);
	printJobList(Jobs);
}
