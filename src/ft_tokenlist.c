/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:42:26 by alallema          #+#    #+#             */
/*   Updated: 2017/03/11 20:21:29 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_token		*ft_tokenew(int type, char *s, int *level)
{
	t_token	*elem;

	if (!(elem = ft_memalloc(sizeof(t_token))))
		return (NULL);
	elem->type = type;
	elem->select = 0;
	elem->bt_level = level[0];
	elem->bc_level = level[1];
	if (s == NULL)
		elem->word = NULL;
	else
		elem->word = s;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void		ft_tokenadd(t_token **begin, t_token *new)
{
	if (*begin != NULL)
	{
		new->next = *begin;
		(*begin)->prev = new;
	}
	*begin = new;
}
/*
void		ft_tokenclear(t_token **list)
{
	t_token	*tmp;
	t_token	*elem;

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
	free(*list);
}


void		ft_tokenclear(t_token **list)
{
	t_token	*tmp;
	t_token	*p;
	t_token	*n;

	tmp = *list;
	if (!tmp)
		return ;
	p = tmp->prev;
	n = tmp->next;
	if (p)
	{
		p->next = n;
		n->prev = tmp;
	}
	else
	{
		*list = n;
		n->prev = NULL;
	}
	if (n)
	{
		p->next = n;
		n->prev = p;
	}
	else
		p->next = NULL;
//	free(tmp);
}
*/
void		ft_tokenpush(t_token **begin, t_token *new)
{
	t_token	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->prev = elem;
}

void		ft_tokendestroy(t_token **begin)
{
	t_token	*tmp;
	t_token	*list;

	list = *begin;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		if (list->word)
			free(list->word);
		list->word = NULL;
		free(list);
		list = tmp;
	}
	*begin = NULL;
}
