/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/02/25 18:52:59 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_recurs_cmd(t_tree *root, t_lst *env)
{
	t_tree	*node;

	node = root;
	if (!node)
		return ;
	if (node->left)
		();
	if (node->right)
		();
	ft_recurs_cmd();
}

static void		ft_waitchild(t_tree *root, t_lst *env)
{
	pid_t	pid;
	int		statval;

	pid = fork();
	close_termios();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		wait(&statval);
		waitpid(pid, &status, 0);
	}
	if (pid == 0)
		ft_recur_cmd(root, env);
}

int				exec_cmd(t_tree *root, t_lst *env)
{
	int		ret;
	t_tree	*node;

	node = root;
	ft_waitchild(node, env);
	ft_putstr_fd("$>", 1);
	return (0);
}
