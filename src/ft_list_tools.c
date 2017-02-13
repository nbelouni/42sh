/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 20:00:04 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 20:06:36 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_print_lst print une liste
*/

void		ft_print_lst(t_lst *lst)
{
	t_elem	*elem;

	if (lst)
	{
		elem = lst->head;
		while (elem)
		{
			write(1, elem->name, ft_strlen(elem->name));
			write(1, "=", 1);
			if (elem->value != NULL)
				write(1, elem->value, ft_strlen(elem->value));
			write(1, "\n", 1);
			elem = elem->next;
		}
	}
}

/*
**	ft_add_elem ajoute un element a la liste d'environnement
**	pointé par g_set->env.
*/

void		ft_add_elem(t_elem *elem, t_lst *lst)
{
	if (elem && lst)
	{
		lst->size++;
		if (lst->head)
		{
			lst->tail->next = elem;
			elem->prev = lst->tail;
		}
		else
		{
			lst->head = elem;
		}
		lst->tail = elem;
	}
}

/*
**	ft_del_elem supprime un element de la liste ainsi que ses variables.
**	(cette fonction est une dumb function (se referer au README))
*/

void		ft_del_elem(t_elem **elem, t_lst *lst)
{
	if ((*elem)->next && (*elem)->prev)
	{
		(*elem)->prev->next = (*elem)->next;
		(*elem)->next->prev = (*elem)->prev;
	}
	else if ((*elem)->next && !(*elem)->prev)
	{
		lst->head = (*elem)->next;
		(*elem)->next->prev = NULL;
	}
	else if (!(*elem)->next && (*elem)->prev)
	{
		lst->tail = (*elem)->prev;
		(*elem)->prev->next = NULL;
	}
	if ((*elem)->name)
		ft_strdel(&((*elem)->name));
	if ((*elem)->value)
		ft_strdel(&((*elem)->value));
	lst->size = lst->size - 1;
	free(*elem);
}

/*
**	ft_find_elem cherche un elem dans la liste pointé par lst,
**	cette fonction retourne l'elem s'il est trouvé, sinon NULL
*/

t_elem		*ft_find_elem(char *name, t_lst *lst)
{
	t_elem	*ptr;

	ptr = NULL;
	if (lst)
	{
		ptr = lst->head;
		while (ptr != NULL)
		{
			if (ptr->name && ft_strcmp(name, ptr->name) == 0)
			{
				return (ptr);
			}
			ptr = ptr->next;
		}
	}
	return (NULL);
}

/*
**	ft_new_elem initialise l'element elem, parse la string str passée en param
**	et qui fait partie de l'env et est donc forcément de format <name>=<value>,
**	value pouvant etre null, puis stock name et value respectivement dans
**	elem->name et elem->value, pour enfin retourner le nouvel element.
*/

t_elem		*ft_new_elem(char *str)
{
	t_elem	*elem;

	if ((elem = ft_init_elem()) == NULL)
	{
		return (NULL);
	}
	if (ft_strchr(str, '='))
	{
		elem->name = ft_strsub(str, 0, ft_get_index_of(str, '='));
		if (elem->name && ft_strlen(str) != (ft_strlen(elem->name) + 1))
		{
			elem->value = ft_strdup(str + ft_strlen(elem->name) + 1);
		}
	}
	return (elem);
}
