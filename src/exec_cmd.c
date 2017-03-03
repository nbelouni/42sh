/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/03/03 23:51:00 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_check_tok(t_tree *root, t_lst *env);
static int		ft_waitchild(t_tree *root, t_lst *env);
/*fork pour execute les cmd char ***/
static void		ft_exec_node(t_tree *node, t_lst *env)
{
	int		statval;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		wait(&statval);
		ft_check_tok(node, env);
	}
	if (pid == 0)
	{
		if (node->token == CMD)
			ft_exec(node->cmd, env);
		else
			exit(0);
	}
}

static void		ft_dot(t_tree *node, t_lst *env)
{
	if (node->left)
		ft_waitchild(node->left, env);
	if (node->right)
		ft_waitchild(node->right, env);
	return ;
}

static void		ft_or_and(t_tree *node, t_lst *env, int token)
{
	if (node->left && ft_waitchild(node->left, env) == token)
	{
		if (node->right)
			ft_waitchild(node->right, env);
	}
	return ;
}
/*check les token et renvoie a la fonctione dediee pour chaque token*/
static void		ft_check_tok(t_tree *root, t_lst *env)
{
	t_tree	*node;
	int		pipefd[2];
	int		fd;
	int		fd2;

	node = root;
	if (!node)
	{
		PUT2("none node\n");
		return ;
	}
	if (node->token == DOT)
		return (ft_dot(node, env));
	if (node->token == OR || node->token == AND)
		return (ft_or_and(node, env, node->token - 11));
	if (node->token == PIPE)
	{
//		PUT2("\n_________pipe______________\n");
		if (pipe(pipefd) < 0)
			ft_putstr_fd("error pipe\n", 2);
		fd = dup(STDOUT_FILENO);
		fd2 = dup(STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	if (node->left)
	{
//		PUT2("\n______________dup left__________\n");
		ft_exec_node(node->left, env);
		dup2(fd, STDOUT_FILENO);
	}
	if (node->right)
	{
		if (close(pipefd[1]) < 0)
			PUT2("error close pipe[1]\n");
//		PUT2("\n________________dup right_________\n");
		dup2(pipefd[0], STDIN_FILENO);
		ft_exec_node(node->right, env);
		dup2(fd2, STDIN_FILENO);
	}
//	PUT2("\n__________end____________\n");
}
/*fork le premier processus ou l'arbre et renvoie TRUE pour chaque vraie commande*/
static int		ft_waitchild(t_tree *root, t_lst *env)
{
	pid_t	pid;
	int		status;

	if (root && root->token == CMD)
		pid = fork();
	else
		pid = 0;
	close_termios();
	if (pid < 0)
		return (FALSE);
	if (pid > 0)
			waitpid(pid, &status, 0);
	if (pid == 0)
	{
		if (root && root->token == CMD)
		{
			if (ft_exec(root->cmd, env) == FALSE)
				return (FALSE);
		}
		else
			ft_check_tok(root, env);
	}
//	PUT2("\n__________true____________\n");
	return (TRUE);
}
/*lance chaque commande*/
int				exec_cmd(t_tree *root, t_lst *env)
{
	t_tree	*node;

	node = root;
	if (ft_waitchild(node, env) == FALSE)
		return (FALSE);
	ft_putstr_fd("\n", 1);
	return (0);
}
