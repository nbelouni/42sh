/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/02/28 00:00:24 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_exec_node(t_tree *root, t_lst *env, int in_fd);

static void		ft_check_tok(t_tree *node, t_lst *env, int in_fd)
{
	int		statval;
	pid_t	pid;
//	int		file;

	(void)in_fd;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		wait(&statval);
		ft_exec_node(node, env, in_fd);
	}
	if (pid == 0)
	{
		if (node->token_or->type == CMD)
			ft_exec(node->token_or->string, env);
		else
			exit(0);
	}
}

static void		ft_exec_node(t_tree *root, t_lst *env, int in_fd)
{
	t_tree	*node;
	int		pipefd[2];

	(void)in_fd;
	node = root;
	if (node->token_or->type == PIPE)
	{
		PUT2("PIPE\n");
		if (pipe(pipefd) < 0)
			ft_putstr_fd("error pipe\n", 2);
		dup2(pipefd[0], in_fd);
//		close(pipefd[0]);
//		dup2(in_fd, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
//		close(pipefd[1]);
	}
	if (!node)
	{
		PUT2("none node\n");
		return ;
	}
	if (node->left)
	{
//		PUT2("node left\n");
		ft_check_tok(node->left, env, pipefd[1]);
	}
	if (node->right)
	{
//		PUT2("node right\n");
		ft_check_tok(node->right, env, pipefd[0]);
	}
//	close(pipefd[1]);
}
/*
static void		ft_find_dot(t_tree *root, t_lst *env)
{
	t_tree	*node;

	(void)env;
	node = root;
	if (!node)
		return ;
	if (node->type == DOT)
		(ft_resurs_tree(node->left, env));
//	if (node->left)
//		();
//	if (node->right)
//		();
//	ft_find_dot(node->left);
//	ft_find_dot(node->right);
}
*/
static void		ft_waitchild(t_tree *root, t_lst *env)
{
	pid_t	pid;
	int		status;

	if (root->token_or->type == CMD)
		pid = fork();
	else
		pid = 0;
	close_termios();
	if (pid < 0)
		return ;
	if (pid > 0)
			waitpid(pid, &status, 0);
	if (pid == 0)
	{
		if (root->token_or->type == CMD)
			ft_exec(root->token_or->string, env);
		else
			ft_exec_node(root, env, STDIN_FILENO);
	}
}

int				exec_cmd(t_tree *root, t_lst *env)
{
	t_tree	*node;

	node = root;
//	ft_find_dot(node);
	ft_waitchild(node, env);
	ft_putstr_fd("\n", 1);
	return (0);
}
