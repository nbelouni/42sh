/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:58:36 by alallema          #+#    #+#             */
/*   Updated: 2017/03/09 17:18:20 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
 ** fonction lancement de groupe de cmd delimitee par le ;
 */
void		ft_dot(t_tree *node, t_lst *env)
{
	if (node->left)
		ft_init_gpr(node->left, env);
	if (node->right)
		ft_init_gpr(node->right, env);
	return ;
}

/*
 **fonction de gestion des pipes
 */
void	 	ft_pipe(t_tree *node, t_lst *env)
{
	int		pipefd[2];
	int		fd;
	int		fd2;

	if (node->token == PIPE)
	{
		if (pipe(pipefd) < 0)
			ft_putstr_fd("error pipe\n", 2);
		fd = dup(STDOUT_FILENO);
		fd2 = dup(STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
	}
	if (node->left)
	{
		ft_exec_node(node->left, env);
		dup2(fd, STDOUT_FILENO);
	}
	if (node->right)
	{
		if (close(pipefd[1]) < 0)
			PUT2("error close pipe[1]\n");
		dup2(pipefd[0], STDIN_FILENO);
		ft_exec_node(node->right, env);
		dup2(fd2, STDIN_FILENO);
	}
}

/*
 **fonction de gestion de || && relance un groupe de cmd
 */
void		ft_or_and(t_tree *node, t_lst *env, int token)
{
	if (node->left && ft_init_gpr(node->left, env) == token)
	{
		if (node->right)
			ft_init_gpr(node->right, env);
	}
	return ;
}

/*
 **fonction de gestion des redirection droite ///EN COURS//
 */
void	 	ft_redir_right(t_tree *node, t_lst *env)
{
	char	buf[255];
	int		fd;
	int		fd2;
	int		pipefd[2];
	int		file;

	ft_bzero(buf, 255);
	if (node->token == SR_DIR)
	{
		PUT2("\n_________dup______________\n");
		if (pipe(pipefd) < 0)
			ft_putstr_fd("error pipe\n", 2);
		fd = dup(STDOUT_FILENO);
		fd2 = dup(STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		if (close(pipefd[1]) < 0)
			PUT2("error close pipe[1]\n");
	}
	if (node->left)
	{
		PUT2("\n______________dup left__________\n");
		ft_exec_node(node->left, env);
		dup2(fd, STDOUT_FILENO);
	}
	if (node->right)
	{
		PUT2(node->right->cmd[0]);
		if ((file = open(node->right->cmd[0], O_WRONLY|O_TRUNC|O_CREAT, 0777)) != -1)
		{
			PUT2("\n________________dup right_________\n");
//			dup2(pipefd[0], STDIN_FILENO);
//			if (node->out)
//			dup2(STDOUT_FILENO, out);
//			dup2(file, pipefd[1]);
//			if (close(pipefd[1]) < 0)
//				PUT2("error close pipe[0]\n");
			dup2(file, pipefd[0]);
//			if (close(pipefd[1]) < 0)
//				PUT2("error close pipe[1]\n");
			read(pipefd[0], &buf, 255);
			PUT2(buf);
			if (close(file) < 0)
				PUT2("error close file\n");
//			ft_exec_node(node->right, env);
		}
		dup2(fd2, STDIN_FILENO);
	}
//	PUT2("\n__________end____________\n");
}
