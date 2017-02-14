/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:13:58 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/12 18:16:30 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_init_set initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type set.
*/

t_set	*ft_init_set(void)
{
	t_set	*set;

	set = NULL;
	if ((set = malloc(sizeof(t_set))) != NULL)
	{
		set->env = NULL;
		set->head = NULL;
		set->tail = NULL;
		return (set);
	}
	return (NULL);
}

/*
**	ft_init_list initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type env.
*/

t_lst	*ft_init_list(void)
{
	t_lst	*lst;

	lst = NULL;
	if ((lst = malloc(sizeof(t_lst))) != NULL)
	{
		lst->head = NULL;
		lst->tail = NULL;
		lst->size = 0;
		return (lst);
	}
	return (NULL);
}

/*
**	ft_init_elem initialise un nouvel element en l'allouant et en mettant tous
**	ses octets a 0, puis retourne le nouvel element.
*/

t_elem	*ft_init_elem(void)
{
	t_elem	*elem;

	elem = NULL;
	if ((elem = malloc(sizeof(t_elem))) != NULL)
	{
		elem->name = NULL;
		elem->value = NULL;
		elem->next = NULL;
		elem->prev = NULL;
		return (elem);
	}
	return (NULL);
}

/*
**	ft_env_to_tab creer un tableau de strings contenant la liste d'env
**	pointé par g_set->env, puis le retourne contenant des strings de format
**	<name> + = + <value>.
*/

char	**ft_env_to_tab(t_lst *lst)
{
	t_elem	*tmp;
	char	**res;
	int		i;

	if (!(res = (char **)malloc(sizeof(char *) * (lst->size + 1))))
		return (NULL);
	ft_memset(res, 0, sizeof(res));
	tmp = lst->head;
	i = 0;
	while (tmp != NULL)
	{
		res[i] = ft_strnew(ft_strlen(tmp->name) + ft_strlen(tmp->value) + 1);
		ft_strcpy(res[i], tmp->name);
		res[i][ft_strlen(tmp->name)] = '=';
		res[i] = ft_strcat(res[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (res);
}

/*
**	ft_env_to_list cree une liste depuis envp et la stock a l'adress
**	de g_set->env, elle ne check pas envp, on assume qu'il n'est pas vide.
*/

t_lst	*ft_env_to_list(char **envp, t_lst *lst)
{
	t_elem	*elem;
	int		i;

	if ((lst = ft_init_list()) == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		elem = ft_new_elem(envp[i]);
		ft_add_elem(elem, lst);
		i++;
	}
	return (lst);
}
