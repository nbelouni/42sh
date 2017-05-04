/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:06:52 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Ft_print_lst print une liste
*/

void		ft_print_lst(t_lst *lst)
{
	t_elem	*elem;

	if (lst != NULL)
	{
		elem = lst->head;
		while (elem != NULL)
		{
			write(1, elem->name, ft_strlen(elem->name));
			write(1, "=", 1);
			if (elem->value != NULL)
			{
				write(1, elem->value, ft_strlen(elem->value));
			}
			write(1, "\n", 1);
			elem = elem->next;
		}
	}
}

/*
**	Ft_add_elem ajoute un element a la liste d'environnement
**	pointé par g_set->env.
*/

void		ft_insert_elem(t_elem *elem, t_lst *lst)
{
	if (elem != NULL && lst != NULL)
	{
		lst->size++;
		if (lst->head != NULL)
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
**	Ft_find_elem cherche un elem dans la liste pointé par lst,
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
**	Ft_new_elem initialise l'element elem, parse la string str passée en param
**	et qui fait partie de l'env et est donc forcément de format <name>=<value>,
**	value pouvant etre null, puis stock name et value respectivement dans
**	elem->name et elem->value, pour enfin retourner le nouvel element.
*/

t_elem		*ft_new_elem(char *s)
{
	t_elem	*elem;

	if ((elem = ft_init_elem()) == NULL)
		return (NULL);
	if ((elem->name = ft_strsub(s, 0, ft_get_index_of(s, '='))) != NULL)
	{
		if (elem->name && ft_strlen(s) != (ft_strlen(elem->name) + 1))
		{
			if (!(elem->value = ft_strdup(s + ft_strlen(elem->name) + 1)))
			{
				ft_clear_elem(&elem);
				return (NULL);
			}
		}
		return (elem);
	}
	ft_clear_elem(&elem);
	return (NULL);
}

/*
**	Ft_add_elem est une fonction qui va checker si un caractere '=' est present
**	, auquel cas ft_new_elem est appellée pour creer un element,
**	puis ft_insert_elem s'occupe de l'introduire dans la liste.
*/

int			ft_add_elem(t_lst *lst, char *s)
{
	t_elem	*elem;

	elem = NULL;
	if (s && s[0])
	{
		if (ft_strchr(s, '='))
		{
			if ((elem = ft_new_elem(s)) == NULL)
				return (ERR_EXIT);
			ft_insert_elem(elem, lst);
			return (0);
		}
	}
	return (-1);
}
