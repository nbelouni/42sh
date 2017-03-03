/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/03/03 16:29:31 by alallema         ###   ########.fr       */
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
	PUT1("fork\n");
	pid = fork();
	ft_bzero(buf, 255);
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		PUT1("recurs\n");
		wait(&statval);
		if (ft_strcmp("wc", node->token_or->word) == 0)
		close(pipefd[0]);
		close(pipefd[1]);
		PUT1("recurs wait\n");
		ft_exec_node(node, env, in_fd);
	}
	if (pid == 0)
	{
		PUT1("exec cmd\n");
		PUT1(node->token_or->word);
		X('\n');
		if (ft_strcmp("wc", node->token_or->word) == 0)
		{
			PUT1("--READ EXEC--\n");
			PUT1(node->token_or->word);
			read(0, &buf, 255);
			ft_putstr_fd(buf, 2);
		}
		PUT1("exec\n");
		if (node->token_or->type == CMD)
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

	(void)in_fd;
	node = root;
	ft_bzero(buf, 255);
	if (node->token_or->type == CMD/* && in_fd != STDIN_FILENO*/)
	{
//		close(in_fd);
	}
	if (node->token_or->type == PIPE)
	{
		PUT1("pipefd\n");
		if (pipe(pipefd) < 0)
			ft_putstr_fd("error pipe\n", 2);
	}
	if (!node)
	{
		PUT1("none node\n");
		return ;
	}
	if (node->left)
	{
		PUT2("dup left\n");
		dup2(pipefd[1], STDOUT_FILENO);
//		close(pipefd[1]);
		ft_check_tok(node->left, env, pipefd, in_fd);
	}
	if (node->right)
	{
		PUT2("dup right\n");
		dup2(pipefd[0], STDIN_FILENO);
//		close(pipefd[0]);
		ft_check_tok(node->right, env, pipefd, in_fd);
	}
//	PUT2("--END--\n");
//	close(pipefd[1]);
//	close(pipefd[0]);
//	close(in_fd);
}

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
