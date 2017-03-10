/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:02 by alallema          #+#    #+#             */
/*   Updated: 2017/03/10 10:57:18 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <errno.h>

static void		ft_check_tok(t_tree *root, t_lst *env);

void			print_gpid()
{
	char	*s;

	s = NULL;
	PUT2("\ntty - terminal: ");
	PUT2(ctermid(s));X('\n');
	PUT2("\npgid groupe process parent: ");
	E(tcgetsid(STDIN_FILENO));X('\n');
	strerror(tcgetsid(STDIN_FILENO));X('\n');
	PUT2("\npid process: ");
	E(getpid());X('\n');
}
/*
 **fork pour execute les cmd
 */
void			ft_exec_node(t_tree *node, t_lst *env)
{
	int		statval;
	pid_t	pid;

	pid = fork();
//	print_gpid();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		wait(&statval);
		ft_check_tok(node, env);
	}
	if (pid == 0)
	{
		if (node->token == CMD && ft_exec_built(env, node->cmd) != 0)
 			ft_check_exec(node->cmd, env);
		else
			exit(0);
	}
}

/*
 **check les token pour chaque noeud et renvoie 
 **sur la fonction dediee pour chaque token
 */
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
//		PUT2("\n_________redir______________\n");
		ft_redir_right(node, env);
	}
	if (node->token == PIPE)
		ft_pipe(node, env);
}

/*
 **attend la fin de l'execution du processus fils
 */
int			ft_waitchild(void)
{
	int		statval;
//	int		status;

		wait(&statval);
		if (WIFEXITED(statval))
		{
			if (WEXITSTATUS(statval) != 0)
				return (FALSE);
		}
		return (TRUE);
//		waitpid(pid, &status, 0);
}

/*
 **fork si c'est une cmd ou envoie a la fonction de check des noeuds
 **retourne le retour de cmd pour chaque cmd reussie
 */
int			ft_init_gpr(t_tree *root, t_lst *env)
{
	pid_t	pid;
//	int		statval;

	if (root && root->token == CMD && ft_check_built(root->cmd) != 0)
		pid = fork();
	else
		pid = 0;
	close_termios();
	if (pid < 0)
		return (FALSE);
	if (pid > 0)
		return (ft_waitchild());
	if (pid == 0)
	{
		if (root && root->token == CMD)
			ft_check_exec(root->cmd, env);
		else
			ft_check_tok(root, env);
	}
	return (TRUE);
}

/*
 **lancement de l'arbre
 */
int				exec_cmd(t_tree *root, t_lst *env)
{
	t_tree	*node;

	node = root;
	ft_init_gpr(node, env);
	return (0);
}
