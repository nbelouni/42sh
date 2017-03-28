/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:13:58 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/20 14:43:44 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_init_set initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type set.
*/

t_core		*ft_init_core(void)
{
	t_core			*set;

	set = NULL;
	if ((set = malloc(sizeof(t_core))) == NULL)
		return (NULL);
	set->env = NULL;
	set->set = NULL;
	set->exp = NULL;
	set->hist = NULL;
	return (set);
}

/*
**	ft_init_list initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type env.
*/

t_lst		*ft_init_list(void)
{
	t_lst		*lst;

	lst = NULL;
	lst = malloc(sizeof(t_lst));
	if (lst == NULL)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	return (lst);
}

/*
**	ft_init_elem initialise un nouvel element en l'allouant et en mettant tous
**	ses octets a 0, puis retourne le nouvel element.
*/

t_elem		*ft_init_elem(void)
{
	t_elem		*elem;

	elem = NULL;
	if ((elem = malloc(sizeof(t_elem))) == NULL)
	{
		return (NULL);
	}
	elem->is_modified = 0;
	elem->is_appended = 0;
	elem->name = NULL;
	elem->value = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

/*
**	ft_env_to_tab creer un tableau de strings contenant la liste d'env
**	pointé par g_set->env, puis le retourne contenant des strings de format
**	<name> + = + <value>.
*/

static char	*ft_envv_to_str(t_elem *elem)
{
	size_t		name_len;
	char		*res;

	name_len = ft_strlen(elem->name);
	if ((res = ft_strnew(name_len + ft_strlen(elem->value) + 1)) == NULL)
	{
		return (NULL);
	}
	ft_strcpy(res, elem->name);
	res[name_len] = '=';
	res = ft_strcat(res, elem->value);
	return (res);
}

char		**ft_env_to_tab(t_lst *lst)
{
	t_elem		*tmp;
	char		**res;
	size_t		i;

	res = NULL;
	if ((res = (char **)malloc(sizeof(char *) * (lst->size + 1))) == NULL)
	{
		return (NULL);
	}
	ft_memset(res, 0, (sizeof(char *) * (lst->size + 1)));
	tmp = lst->head;
	i = 0;
	while (tmp != NULL)
	{
		if ((res[i] = ft_envv_to_str(tmp)) == NULL)
		{
			ft_tabdel(res);
			return (NULL);
		}
		++i;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

/*
**	ft_env_to_list cree une liste depuis envp et la stock a l'adress
**	de g_set->env, elle ne check pas envp, on assume qu'il n'est pas vide.
*/

t_lst		*ft_env_to_list(char **envp, t_lst *lst)
{
	int			ret;

	if ((lst = ft_init_list()) == NULL)
	{
		return (NULL);
	}
	ret = 0;
	if (*envp != NULL)
	{
		while (*envp != NULL)
		{
			if ((ret = ft_add_elem(lst, *envp)) != 0)
			{
				if (ret == ERR_EXIT)
				{
					(lst) ? ft_del_list(lst) : 0;
				}
				return (NULL);
			}
			++envp;
		}
	}
	return (lst);
}
