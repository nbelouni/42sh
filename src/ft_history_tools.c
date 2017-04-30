/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:46:55 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/30 22:53:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Ft_get_hfname va récuperer le path du fichier d'historique contenu dans
**	la variable du set HISTFILE. Si cette valeur est NULL, NULL est retourné.
*/

char		*ft_get_hfname(t_lst *set)
{
	t_elem	*elem;

	elem = NULL;
	if ((elem = ft_find_elem("HISTFILE", set)) == NULL)
	{
		return (NULL);
	}
	if (elem->value == NULL || elem->value[0] == '\0')
	{
		return (NULL);
	}
	return (elem->value);
}

/*
**	Ft_chech_history_var est une fonction qui va checker les variables du set
**	liées a l'historique a chaque tour de boucle du shell, afin de tronquer
**	le fichier et/ou la liste d'historique.
*/

int			ft_check_history_var(t_lst *set, t_lst *hist)
{
	int		hsize;
	int		hfsize;
	char	*hfname;

	if ((hsize = ft_get_hsize(set)) >= 0)
	{
		ft_truncate_histlist(hist, (size_t)hsize);
	}
	if ((hfname = ft_get_hfname(set)) != NULL)
	{
		if ((hfsize = ft_get_hfsize(set)) >= 0)
		{
			if ((hsize = ft_truncate_histfile(hfname, hfsize)) < 0)
			{
				return (hsize);
			}
		}
	}
	return (0);
}

/*
**	Ft_cmd_to_history est une fonction qui, comme son nom l'indique, va push
**	la ligne de commande, entrée dans l'entrée standard, dans la liste hist.
*/

int			ft_cmd_to_history(t_lst *hist, char *cmd)
{
	t_elem	*new_elem;

	new_elem = NULL;
	if ((new_elem = ft_init_elem()) == NULL)
	{
		return (ERR_EXIT);
	}
	if (cmd == NULL || cmd[0] == '\n' || cmd[0] == '\0')
	{
		free(new_elem);
		return (0);
	}
	if ((new_elem->name = ft_strdup(cmd)) == NULL)
	{
		free(new_elem);
		return (ERR_EXIT);
	}
	ft_insert_elem(new_elem, hist);
	return (0);
}

/*
**	Ft_print_history est la fonction de l'affichage de l'historique. L'int
**	qu'elle prend en parametre va definir a partir de quel element la liste
**	d'historique hist va etre affichée. Si une commande de l'historique
**	a été modifiée, un caractere '*' est affiché devant ce dernier.
*/

int			ft_print_history(t_lst *hist, int start)
{
	int		i;
	t_elem	*tmp;

	if (start < 0)
		return (0);
	if (start >= (int)hist->size)
		tmp = hist->head;
	else
		tmp = ft_get_nelem(hist, (hist->size - start));
	i = (tmp == hist->head) ? 1 : (hist->size - start);
	while (tmp != NULL)
	{
		if (tmp->name != NULL && tmp->name[0] != '\0')
		{
			ft_putnbr(i);
			(tmp->is_modified == 1) ? write(1, "*", 1) : 0;
			ft_putnchar(' ', (7 - ft_intlen(i)));
			ft_putendl_fd(tmp->name, 1);
		}
		tmp = tmp->next;
		++i;
	}
	return (0);
}

/*
**	Fonction utilisee lorsque une autre fonction liee a l'historique a besoin
**	de verifier si filename est NULL, auquel cas HISTFILE est recherche dans
**	le set et le pointeur sur filename pointe sur la value, si elle existe,
**	de la variable HISTFILE, sinon NULL est retourne.
*/

char		*ft_check_hist_filename(t_lst *set, char *filename)
{
	t_elem	*elem;

	if (filename == NULL || filename[0] == '\0')
	{
		if ((elem = ft_find_elem("HISTFILE", set)) == NULL)
		{
			return (NULL);
		}
		if (elem->value == NULL || elem->value[0] == '\0')
		{
			return (NULL);
		}
		filename = elem->value;
	}
	return (filename);
}
