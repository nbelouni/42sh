/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:52:27 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/15 16:56:01 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

#define is ==
#define token(x) (((t_tree *)x)->token)
#define isCondition(x) (x == OR || x == AND)
#define isRedir(x) (x == DIR_AMP || x == SR_DIR || x == SL_DIR || x == DR_DIR || x == DL_DIR)

void	*iterAst(t_tree *ptr)
{
	List_p	stock;

	stock = NULL;
	while (ptr)
	{
		push(&stock, ptr);
		ptr = ptr->left;
	}
	return (stock);
}

Node_p	createProcessTree(t_tree *root)
{
	List_p	stack;
	List_p	stock;

	stock = NULL;
	while (true)
	{
		if (token(top(stock)) is CMD)
			push(&stack, createProcess(pop(&stock)));
		if (isCondition(token(top(stock))))
			push(&stack, createConditionIf(pop(&stock), pop(&stack), pop(&stack)));//Condition, rightNode, leftNode
		if (token(top(stock)) is PIPE)
			push(&stack, createPipe(pop(&stack), pop(&stack)));//rightNode, leftNode
		if (isRedir(token(top(stock))))
			push(&stack, createRedir(pop(&stock), pop(&stack)));//Redir, targetNode, leftNode		
		if (((t_tree *)top(stock))->right)
			push(&stock,iterAst(root));
		if (!stock)
			break;
	}
	return (pop(&stack));
}

t_job	*create_job(t_tree *root, int foreground)
{
	t_job	*job;

	job = ft_memalloc(sizeof(t_job));
	job->foreground = foreground;
	job->process_tree = createProcessTree(root);
	return (job);
}

void	export_job(t_tree *root, List_p *job_list)
{
	t_tree	*ptr;

	ptr = root;
	while (ptr)
	{
		if (token(ptr) != AMP && token(ptr) != DOT)
			insertLinkBottom(job_list, newLink(create_job(ptr, 0), sizeof(**job_list)));
		else
		{
			ptr = ptr->left;
			insertLinkBottom(job_list, newLink(create_job(ptr, 1), sizeof(**job_list)));
		}
		ptr = ptr->right;
	}
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
	ptr->data = newProcess(nodeProcess->cmd);
	return (ptr);
}

Node_p	createConditionIf(t_tree *nodeConditionIf, Node_p rightNode, Node_p leftNode)
{
	Node_p ptr;

	ptr = newNode(IF, sizeof(struct ConditionIf));
	ptr->left = leftNode;
	ptr->right = rightNode;
	ptr->data = newConditionIf((token(nodeConditionIf) is OR)? IF_OR: IF_AND);
	return (ptr);
}

Node_p	createPipe(Node_p rightNode, Node_p leftNode)
{
	insertLinkBottom(&((Process_p)leftNode->data)->next, rightNode->data);
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

void	listIter(List_p list, (void)f(void *))
{
	while (list)
	{
		f(list->data);
		list = list->next;
	}
}

void spacer(char *Param, int io);
{
	static int depth;
	
	for (int i = 0; i < dept ; i++)
	{
		putchar('|');
		putchar('\t');
	}
	depth += io;
}

void printJobList(List_p jobList)
{
	listIter(jobList, &printJob);
}

void printJob(t_job *job)
{
	spacer(1);
	printf("[JOB]\t");
	printf("Command : <%s>\t", job->command);
	printf("Foreground : <%d>\t", job->foreground);
	printf("Next Job 0xAdd : <%p>\n", job->next);
	printNode(job->process_tree);
	spacer(-1);
}

void printNode(Node_p processTree)
{
	spacer(1);
	printf("[NODE]\n");
	if (processTree->type is PROCESS)
		printProcessList(ProcessTree->data);
	else
	{
		printConditionIf(processTree->data);
		printNode(processTree->left);
		printNode(processTree->right);
	}
	spacer(-1);
}

void printProcessList(List_p processList)
{
	listIter(processList, &printProcess);
}

void printProcess(Process_p process)
{
	spacer(1);
	printf("[PROCESS]\t");
	printf("command : <%s>\t", (process->argv)[0]);
	for (int i = 1; (process->argv)[i];  i++)
		printf("A%d: <%s>\t", (process->argv)[i]);
	printf("self: <%p>\t", &process);
	printf("Next Process 0xAdd : <%p>\n", process->next);
	printNode(job->process_tree);
	spacer(-1);
}

void printConditionIf(ConditionIf_p condition)
{
	spacer(1);
	printf("[CONDITION]\t");
	printf("Command : <%s>\t", job->command);
	printf("self: <%p>\t", &job);
	printf("left: <%p>\t", job->left);
	printf("right: <%p>\n", job->right);
	printNode(job->process_tree);
	spacer(-1);
}	
