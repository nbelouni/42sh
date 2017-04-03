/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:06:09 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/20 13:05:15 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Similaire a ft_get_histfilesize, a l'exception du check de la valeur < 0.
**	Fonction qui definit le comportement des fonctions de manipulation
**	de l'historique selon la variable HISTFILESIZE contenue dans la liste set,
**	si cette variable n'existe pas, que sa value est NULL, que la valeur
**	digitale de cette derniere n'est pas entierement digitale, le stockage
**	dans le fichier n'a pas de limite. Si aucun de ces cas n'est trouvé,
**	la valeur digitale de la value est renvoyée.
*/

int		ft_get_hsize(t_lst *set)
{
	int			ret;
	t_elem		*elem;

	elem = NULL;
	if ((elem = ft_find_elem("HISTSIZE", set)) == NULL)
	{
		return (-1);
	}
	if (elem->value == NULL || elem->value[0] == '\0')
	{
		return (-1);
	}
	if (ft_strisdigit(elem->value) == 0)
	{
		return (-1);
	}
	ret = ft_atoi(elem->value);
	if (ret <= 0)
	{
		return (0);
	}
	return (ft_atoi(elem->value));
}

/*
**	Fonction qui va prendre chaques lignes du fichier pointe par fd,
**	afin de les ajouter a la liste histlist.
*/

t_lst	*ft_histfile_to_histlist(t_lst *histlist, int fd)
{
	t_elem		*elem;
	char		*buf;

	buf = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		if ((elem = ft_init_elem()) == NULL)
			return (NULL);
		if ((elem->name = ft_strdup(buf)) == NULL)
		{
			ft_del_elem(&elem, histlist);
			return (NULL);
		}
		elem->is_appended = 1;
		ft_insert_elem(elem, histlist);
		ft_strdel(&buf);
	}
	return (histlist);
}

/*
**	Fonction qui va recuperer le contenu du fichier d'historique selon
**	la valeur d'HISTSIZE, dont l'interpretation de cette valeur est faite
**	via ft_get_hsize.
*/

int		ft_get_histfile_content(t_lst *hist, int fd)
{
	if ((hist = ft_histfile_to_histlist(hist, fd)) == NULL)
	{
		return (ERR_EXIT);
	}
	return (0);
}

/*
**	Fonction qui va recuperer l'historique depuis la valeur d'HISTFILE.
**	Si HISTFILE n'existe pas ou que sa value est NULL ou que le fichier
**	n'a pas les droits, une erreur est renvoyee. Sinon, l'historique
**	est ajoute a la liste via ft_get_histfile_content.
*/

t_lst	*ft_get_history(t_lst *hist, char *filename)
{
	int			fd;
	struct stat	st;

	if (hist == NULL)
	{
		if ((hist = ft_init_list()) == NULL)
			return (NULL);
	}
	if ((fd = open(filename, O_RDWR | O_CREAT, 0777)) == -1)
	{
		ft_print_error(filename, ERR_NO_ACCESS, -1);
		return (hist);
	}
	if ((lstat(filename, &st)) == -1)
		return (hist);
	if (st.st_size > 0)
	{
		if ((ft_get_histfile_content(hist, fd)) == ERR_EXIT)
		{
			ft_del_list(hist);
			hist = NULL;
		}
	}
	close(fd);
	return (hist);
}
