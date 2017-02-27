/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/02/27 19:59:49 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_exec_node(t_tree *root, t_lst *env);

static void		ft_check_tok(t_tree *node, t_lst *env)
{
	int		statval;
	pid_t	pid;
//	int		pipefd[2];
//	int		file;

	pid = fork();
//	pipe(pipefd);
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		wait(&statval);
		ft_exec_node(node, env);
	}
	if (pid == 0)
	{
		if (node->token_or->type == CMD)
			ft_exec(node->token_or->string, env);
		else
			exit(0);
	}
}

static void		ft_exec_node(t_tree *root, t_lst *env)
{
//	int		statval;
	t_tree	*node;

	(void)env;
	node = root;
	if (!node)
	{
		PUT2("none node\n");
		return ;
	}
	if (node->left)
	{
//		PUT2("node left\n");
		ft_check_tok(node->left, env);
	}
	if (node->right)
	{
//		PUT2("node right\n");
		ft_check_tok(node->right, env);
	}
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
			ft_exec_node(root, env);
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
