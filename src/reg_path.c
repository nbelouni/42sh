/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:58:45 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/23 18:55:51 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_reg_path		*ft_reg_pathnew(char *path, char *out, int lvl, t_bool is_abs)
{
	t_reg_path	*elem;

	if (!(elem = ft_memalloc(sizeof(t_reg_path))))
		return (NULL);
	elem->level = lvl;
	elem->is_abs = is_abs;
	if (path == NULL)
		elem->path = NULL;
	else
		elem->path = path;
	if (out == NULL)
		elem->out = NULL;
	else
		elem->out = out;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void		ft_reg_pathadd(t_reg_path **begin, t_reg_path *new)
{
	if (*begin != NULL)
	{
		new->next = *begin;
		(*begin)->prev = new;
	}
	*begin = new;
}

void		ft_reg_pathclear(t_reg_path **list)
{
	t_reg_path	*tmp;
	t_reg_path	*elem;

	if (list == NULL)
		return ;
	elem = (*list)->prev;
	tmp = (*list)->next;
	if (!elem)
		*list = (*list)->next;
	else
	{
		elem->next = tmp;
		tmp->prev = elem;
	}
	ft_memdel((void *)list);
}

void		ft_reg_pathpush(t_reg_path **begin, t_reg_path *new)
{
	t_reg_path	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->prev = elem;
}

void		ft_reg_pathdestroy(t_reg_path **begin)
{
	t_reg_path	*tmp;
	t_reg_path	*list;

	list = *begin;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		if (list->path)
			ft_strdel(&(list->path));
		if (list->out)
			ft_strdel(&(list->out));
		free(list);
		list = tmp;
	}
	*begin = NULL;
}
