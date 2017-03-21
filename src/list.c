/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 20:01:32 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/21 16:10:35 by llaffile         ###   ########.fr       */
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

void	delete_list(List_p *refHead, void(f)(void *))
{
	while (*refHead)
	{
		f(delete_link(*refHead));
		refHead = &(*refHead)->next;
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
