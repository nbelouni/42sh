/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/03/03 22:12:12 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_exec_node(t_tree *root, t_lst *env, int in_fd);

static void		ft_check_tok(t_tree *node, t_lst *env, int *pipefd, int in_fd)
{
	int		statval;
	pid_t	pid;
	char	buf[255];

	(void)in_fd;
	(void)pipefd;
	(void)statval;
	pid = fork();
	ft_bzero(buf, 255);
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		wait(&statval);
		ft_exec_node(node, env, pipefd[1]);
	}
	if (pid == 0)
	{
		if (node->token == CMD)
			ft_exec(node->cmd, env);
		else
			exit(0);
	}
}

static void		ft_exec_node(t_tree *root, t_lst *env, int in_fd)
{
	char	buf[255];
	t_tree	*node;
	int		pipefd[2];
	int		fd;
	int		fd2;

	(void)in_fd;
	(void)fd;
	node = root;
	ft_bzero(buf, 255);
	if (!node)
	{
		PUT2("none node\n");
		return ;
	}
	if (node->token == PIPE)
	{
		PUT2("\n_________pipe______________\n");
		if (pipe(pipefd) < 0)
			ft_putstr_fd("error pipe\n", 2);
		fd = dup(STDOUT_FILENO);
		dup2(in_fd, STDOUT_FILENO);
		fd2 = dup(STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	if (node->left)
	{
		PUT2("\n______________dup left__________\n");
		ft_check_tok(node->left, env, pipefd, in_fd);
		dup2(fd, STDOUT_FILENO);
	}
	if (node->right)
	{
		if (close(pipefd[1]) < 0)
			PUT2("error close pipe[1]\n");
		PUT2("\n________________dup right_________\n");
		dup2(pipefd[0], STDIN_FILENO);
		ft_check_tok(node->right, env, pipefd, in_fd);
		dup2(fd2, STDIN_FILENO);
	}
	PUT2("\n__________end____________\n");
}

static void		ft_waitchild(t_tree *root, t_lst *env)
{
	pid_t	pid;
	int		status;

	if (root && root->token == CMD)
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
		if (root && root->token == CMD)
			ft_exec(root->cmd, env);
		else
			ft_exec_node(root, env, STDOUT_FILENO);
	}
}

int				exec_cmd(t_tree *root, t_lst *env)
{
	t_tree	*node;

	node = root;
	ft_waitchild(node, env);
	ft_putstr_fd("\n", 1);
	return (0);
}
