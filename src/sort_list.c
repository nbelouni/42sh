/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:14:54 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/02 22:25:51 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_sort_list	*create_sort_list(char *s)
{
	t_sort_list	*elem;

	if (!s)
		return (NULL);
	if (!(elem = ft_memalloc(sizeof(t_sort_list))))
		return (NULL);
	elem->s = s;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void		push_sort_list(t_sort_list **begin, t_sort_list *new)
{
	t_sort_list	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->prev = elem;
}

void		clear_sort_list(t_sort_list *cmd)
{
	if (cmd->s)
		free(cmd->s);
	cmd->s = NULL;
}

void		rm_sort_list(t_sort_list **cmd)
{
	t_sort_list	*tmp;
	t_sort_list	*elem;

	if (cmd == NULL)
		return ;
	elem = (*cmd)->prev;
	tmp = (*cmd)->next;
	if (!elem)
		*cmd = (*cmd)->next;
	else
	{
		elem->next = tmp;
		tmp->prev = elem;
	}
	ft_memdel((void *)cmd);
}

void		destroy_sort_list(t_sort_list **begin)
{
	t_sort_list	*tmp;
	t_sort_list	*list;

	list = *begin;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		clear_sort_list(list);
		free(list);
		list = tmp;
	}
	*begin = NULL;
}
