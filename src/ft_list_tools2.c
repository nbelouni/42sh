/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:18:08 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/21 17:40:38 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_lstclr s'occupe, comme son nom l'indique, clear la liste pointée
**	par lst, sans utiliser free sur l'architecture principale, elle ne free
**	que les elements contenus dans la liste.
*/

void		ft_lstclr(t_lst *lst)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = lst->head;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		ft_del_elem(&tmp, lst);
		tmp = tmp2;
	}
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
}

/*
**	ft_get_nelem va parcourir la liste lst n fois, la particularité est que
**	si n est plus grand que la moitié de la taille de la liste, la recherche
**	d'element se faire depuis la fin de la liste.
*/

t_elem		*ft_get_nelem(t_lst *lst, int n)
{
	t_elem	*elem;
	int		i;
	int		cond;

	cond = ((lst->size / 2) > (size_t)n) ? 1 : -1;
	elem = (cond == 1) ? lst->head : lst->tail;
	i = (cond == 1) ? 1 : (int)lst->size;
	while (i != n)
	{
		if (!elem)
			return (NULL);
		elem = (cond == 1) ? elem->next : elem->prev;
		i += cond;
	}
	return (elem);
}

/*
**	ft_lstcpy va copié la liste src dans dst puis la retourner, la structure
**	n'est pas allouee mais les elements le sont.
*/

t_lst		*ft_lstcpy(t_lst *dst, t_lst *src)
{
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = src->head;
	tmp2 = dst->head;
	while (tmp != NULL)
	{
		if ((tmp2 = ft_elemdup(tmp)) == NULL)
			return (NULL);
		ft_insert_elem(tmp2, dst);
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	return (dst);
}

/*
**	ft_elemdup va creer l'element elem2 en allouant ce dernier a la taille
**	et au contenu de l'element elem1
*/

t_elem		*ft_elemdup(t_elem *elem1)
{
	t_elem	*elem2;

	elem2 = NULL;
	if ((elem2 = ft_init_elem()) == NULL)
		return (NULL);
	if ((elem2->name = ft_strdup(elem1->name)) == NULL)
		return (NULL);
	if (elem1->value != NULL && elem1->value[0] != '\0')
	{
		if ((elem2->value = ft_strdup(elem1->value)) == NULL)
			return (NULL);
	}
	return (elem2);
}

/*
**	ft_lstdup va creer la liste dup_lst en allouant cette derniere a la taille
**	et au contenu de la liste to_dup.
*/

t_lst		*ft_lstdup(t_lst *to_dup)
{
	t_lst	*dup_lst;

	dup_lst = NULL;
	if ((dup_lst = ft_init_list()) == NULL)
	{
		return (NULL);
	}
	if ((dup_lst = ft_lstcpy(dup_lst, to_dup)) == NULL)
	{
		ft_del_list(dup_lst);
	}
	return (dup_lst);
}
