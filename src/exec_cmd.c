/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/03/01 19:37:16 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_exec_node(t_tree *root, t_lst *env, int in_fd);

static void		ft_check_tok(t_tree *node, t_lst *env, int in_fd)
{
	int		statval;
	pid_t	pid;
	char	buf[255];

	(void)in_fd;
	pid = fork();
	ft_bzero(buf, 255);
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		PUT2("wait cmd\n");
		wait(&statval);
		ft_exec_node(node, env, in_fd);
	}
	if (pid == 0)
	{
		PUT2("exec cmd\n");
		PUT2(node->token_or->word);
		X('\n');
		if (ft_strcmp("wc", node->token_or->word) == 0)
		{
			PUT2("--READ EXEC--\n");
//			dup2(in_fd, STDIN_FILENO);
//			close(in_fd);
			PUT2(node->token_or->word);
			read(STDIN_FILENO, &buf, 255);
//			close(STDIN_FILENO);
			ft_putstr_fd(buf, 2);
		}
		if (node->token_or->type == CMD)
			ft_exec(node->token_or->string, env);
		else
			exit(0);
	}
}

static void		ft_exec_node(t_tree *root, t_lst *env, int in_fd)
{
	char	buf[255];
	t_tree	*node;
	int		pipefd[2];

	(void)in_fd;
	node = root;
	ft_bzero(buf, 255);
	if (node->token_or->type == CMD && in_fd != STDIN_FILENO)
	{
		PUT2("CLOSE\n");
//		dup2(in_fd, STDIN_FILENO);
//		close(in_fd);
	}
	if (node->token_or->type == PIPE)
	{
		PUT2("PIPE\n");
		if (pipe(pipefd) < 0)
			ft_putstr_fd("error pipe\n", 2);
//		close(pipefd[0]);
//		dup2(in_fd, STDIN_FILENO);
//		dup2(pipefd[1], STDOUT_FILENO);
//		close(pipefd[1]);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
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
		ft_check_tok(node->right, env, pipefd[1]);
	}
	PUT2("--END--\n");
//	close(pipefd[1]);
//	close(in_fd);
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
