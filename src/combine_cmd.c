/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:52:53 by alallema          #+#    #+#             */
/*   Updated: 2017/04/08 17:58:03 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

/*
** fonctionne avec create_cmd_for_job
** iter sur la liste des job et des processus
** pour recuperer la commande a afficher pour job
*/

/*
** iter sur la pipeline et join les commandes pour les retourner a l'iterateur
*/

static char		*listiter_cmd(t_list *lst, char *(*f)(t_list *elem), int i)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	while (lst && f)
	{
		s = ft_fix_join(s, (*f)(lst->content));
		tmp = s;
		if (lst->next && i)
		{
			s = ft_strjoin(tmp, "| ");
			free(tmp);
		}
		lst = lst->next;
	}
	return (s);
}

/*
** iterateur de liste qui concatene les redirection et les retourne
*/

char			*iter_iolist_cmd(t_list *io_list)
{
	return (listiter_cmd(io_list, (void *)copy_redir, 0));
}

/*
** iterateur de liste qui concatene chaque commande de
** chaque process et les retourne prend la liste de process au depart
** d'un noeud
*/

static char		*iter_process_cmd(t_list *process_list)
{
	return (listiter_cmd(process_list, (void *)copy_process, 1));
}

/*
** recupere le premier noeud de l'arbre de process et iter dessus en
** fonction des noeuds conditions
*/

char			*iter_cmd(t_node_p process_tree)
{
	char	*s;
	char	*tmp;

	s = NULL;
	if (process_tree->type == PROCESS)
		s = iter_process_cmd(process_tree->data);
	else
	{
		if (((t_condition_if_p)process_tree->data)->type == IF_OR)
			tmp = ft_strdup("|| ");
		else
			tmp = ft_strdup("&& ");
		s = ft_fix_join(iter_cmd(process_tree->left), tmp);
		tmp = s;
		s = ft_fix_join(tmp, iter_cmd(process_tree->right));
	}
	return (s);
}
