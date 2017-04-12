/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 20:01:32 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/10 20:03:34 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*new_link(void *content, size_t content_size)
{
	t_list	*link;

	link = malloc(sizeof(*link));
	bzero(link, sizeof(*link));
	link->content = content;
	link->content_size = content_size;
	return (link);
}

void	delete_list(t_list **ref_head, void (f)(void *))
{
	void	*ptr;

	while (*ref_head)
	{
		ptr = delete_link(remove_link_top(ref_head));
		if (f)
			f(ptr);
	}
}

void	*delete_link(t_list *link)
{
	void	*content;

	content = link->content;
	free(link);
	return (content);
}

void	*remove_link_content(t_list **ref_head, void *content)
{
	while (*ref_head)
	{
		if ((*ref_head)->content == content)
			return (remove_link_top(ref_head));
		ref_head = &(*ref_head)->next;
	}
	return (content);
}

void	*remove_link_top(t_list **ref_head_top)
{
	t_list	*link;

	link = *ref_head_top;
	(*ref_head_top) = (*ref_head_top)->next;
	link->next = NULL;
	return (link);
}

void	insert_link_top(t_list **ref_head_top, t_list *sub_link_chain)
{
	t_list	*link;

	link = sub_link_chain;
	while (link->next)
		link = link->next;
	link->next = *ref_head_top;
	*ref_head_top = sub_link_chain;
}

void	insert_link_bottom(t_list **ref_head_top, t_list *sub_link_chain)
{
	while (*ref_head_top)
		ref_head_top = &(*ref_head_top)->next;
	*ref_head_top = sub_link_chain;
}

void	list_iter(t_list *list, void (f)(void *))
{
	while (list)
	{
		f(list->content);
		list = list->next;
	}
}

void	*list_iter_while(t_list *list, void *(f)(void *))
{
	void	*result;

	while (list)
	{
		if ((result = f(list->content)))
			return (result);
		list = list->next;
	}
	return (NULL);
}

void	*list_get_nth(t_list *list, uint32_t nth)
{	
	while (list)
	{
		--nth;
		if (!nth)
			return (list->content);
		list = list->next;
	}
	return (NULL);
}
