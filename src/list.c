/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 20:01:32 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/04 21:56:47 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*new_link(void *content, size_t content_size)
{
	List_p	link;

	link = malloc(sizeof(*link));
	bzero(link, sizeof(*link));
	link->content = content;
	link->content_size = content_size;
	return (link);
}

void	delete_list(List_p *refHead, void (f)(void *))
{
	void *ptr;
	
	while (*refHead)
	{
		ptr = delete_link(remove_link_top(refHead));
		if (f)
			f(ptr);
	}
}

void	*delete_link(List_p link)
{
	void	*content;

	content = link->content;
	free(link);
	return (content);
}

void	*remove_link_content(List_p *refHead, void *content)
{
	while (*refHead)
	{
		if ((*refHead)->content == content)
			return (remove_link_top(refHead));
		refHead = &(*refHead)->next;
	}
	return (content);
}

void	*remove_link_top(List_p *refHeadTop)
{
	List_p	link;

	link = *refHeadTop;
	(*refHeadTop) = (*refHeadTop)->next;
	link->next = NULL;
	return (link);
}

void	insert_link_top(List_p *refHeadTop, List_p subLinkChain)
{
	List_p	link;

	link = subLinkChain;
	while (link->next)
		link = link->next;
	link->next = *refHeadTop;
	*refHeadTop = subLinkChain;
}

void	insert_link_bottom(List_p *refHeadTop, List_p subLinkChain)
{
	while (*refHeadTop)
		refHeadTop = &(*refHeadTop)->next;
	*refHeadTop = subLinkChain;
}

void	list_iter(List_p list, void (f)(void *))
{
	while (list)
	{
		f(list->content);
		list = list->next;
	}
}

void	*list_iter_while(List_p list, void *(f)(void *))
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

void	*list_get_nth(List_p list, uint32_t nth)
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
