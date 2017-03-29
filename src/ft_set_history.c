/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:22:15 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/16 19:28:13 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Similaire a ft_get_hsize, a l'exception du check de la valeur < 0.
**	Fonction qui definit le comportement des fonctions de manipulation
**	de l'historique selon la variable HISTFILESIZE contenue dans la liste set,
**	si cette variable n'existe pas, que sa value est NULL, que la valeur
**	digitale de cette derniere est negative ou qu'elle n'est pas entierement
**	digitale, le stockage dans le fichier n'a pas de limite. Si aucun de ces
**	cas n'est trouvé, la valeur digitale de la value est renvoyée.
*/

int			ft_get_hfsize(t_lst *set)
{
	t_elem	*elem;
	int		ret;

	if ((elem = ft_find_elem("HISTFILESIZE", set)) == NULL)
	{
		return (-1);
	}
	if (elem->value == NULL || elem->value[0] == '\0')
	{
		return (-1);
	}
	ret = ft_atoi(elem->value);
	if (!ft_strisdigit(elem->value) || ret < 0)
	{
		return (-1);
	}
	return (ret);
}

/*
**	Fonction qui copie la liste d'historique dans le fd du fichier
**	d'historique. La copie s'effectue selon la taille de la variable
**	HISTFILESIZE, checkée dans la fonction qui appelle ft_histlist_to_histfile.
**	Si cette valeur est a -1, le comportement de la copie veut qu'elle soit
**	sans limite. En revanche, si elle a une valeur n, forcement superieure a 0
**	(checké dans la fonction mere), seuls les n derniers elements de la liste
**	seront copiés.
*/

int			ft_histlist_to_histfile(t_lst **hist, int fd)
{
	t_elem	*elem;

	elem = (*hist)->head;
	while (elem != NULL)
	{
		ft_putendl_fd(elem->name, fd);
		elem = elem->next;
	}
	return (0);
}

/*
**	Fonction qui va checker si le fichier existe, auquel cas elle va tronquer
**	ce dernier a une taille 0, sinon elle va le cree. Le fait de checker avec
**	le flag O_RDWR permet de savoir si ce dernier est accessible en lecture
**	et ecriture, si ce n'est pas le cas, -1 est retourné et la fonction
**	s'arrete. Si la fonction continue, la valeur d'HISTFILESIZE (histfsize)
**	est checker afin de voir si 0 a ete retourne (signifiant un tronquage)
**	a taille 0 sans possibilité de stocker quoi que ce soit dans le fichier
**	filename. Si aucune erreur n'est trouvee, ft_histlist_to_histfile est
**	appellee.
*/

int			ft_check_histfile(t_lst *hist, char *filename)
{
	int		fd;

	if ((fd = open(filename, O_CREAT | O_EXCL)) == ERR_NEW_CMD)
	{
		fd = open(filename, O_RDWR | O_TRUNC);
	}
	else
	{
		fd = open(filename, O_RDWR | O_CREAT);
	}
	if (fd == ERR_NEW_CMD)
	{
		return (ERR_NEW_CMD);
	}
	ft_histlist_to_histfile(&hist, fd);
	close(fd);
	return (0);
}

/*
**	Cette fonction va copier la liste d'historique dans la valeur d'HISTFILE.
**	Si HISTFILE n'est pas set, ou que sa valeur est NULL, la liste d'historique
**	n'est pas sauvegardée, sinon ft_check_histfile est appelée avec la value
**	d'HISTFILESIZE trouvee par ft_get_histfilesize.
*/

int			ft_set_history(t_lst *hist, char *filename)
{
	return (ft_check_histfile(hist, filename));
}
