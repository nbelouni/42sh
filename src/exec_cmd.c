/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/03/08 13:24:49 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void		ft_check_tok(t_tree *root, t_lst *env);
/*fork pour execute les cmd char ** */
void			ft_exec_node(t_tree *node, t_lst *env)
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
			ft_check_exec(node->cmd, env);
		else
			exit(0);
	}
}

/*check les token et renvoie a la fonctione dediee pour chaque token*/
static void		ft_check_tok(t_tree *root, t_lst *env)
{
	t_tree	*node;

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
	if (node->token == SR_DIR)
	{
		PUT2("\n_________redir______________\n");
		ft_redir_right(node, env);
	}
	if (node->token == PIPE)
		ft_pipe(node, env);
	PUT2("\n_________end node____________\n");
}

/*fork si c'est une cmd et envoie a la fonction de fork de l'arbre et renvoie retour de cmd pour chaque cmd reussie*/
int			ft_waitchild(t_tree *root, t_lst *env)
{
	pid_t	pid;
//	int		status;
	int		statval;

	if (root && root->token == CMD && ft_check_built(root->cmd) != 0)
		pid = fork();
	else
		pid = 0;
	close_termios();
	if (pid < 0)
		return (FALSE);
	if (pid > 0)
	{
		wait(&statval);
		if (WIFEXITED(statval))
		{
			if (WEXITSTATUS(statval) != 0)
				return (FALSE);
		}
//		waitpid(pid, &status, 0);
	}
	if (pid == 0)
	{
		if (root && root->token == CMD)
			ft_check_exec(root->cmd, env);
		else
			ft_check_tok(root, env);
	}
	return (TRUE);
}

/*lance chaque commande*/
int				exec_cmd(t_tree *root, t_lst *env)
{
	t_tree	*node;

	node = root;
	ft_waitchild(node, env);
	return (0);
}
