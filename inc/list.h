/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 19:57:37 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/23 05:38:08 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIST_H
# define LIST_H

# include "42sh.h"

# define PUSH(x, elem)	(insert_link_top(x, new_link(elem, sizeof(elem))))
# define TOP(x)			(x->content)
# define POP(x)			(delete_link(remove_link_top(x)))

typedef struct s_list *List_p;
/*
struct	s_list
{
	List_p	next;
	void	*content;
	size_t	content_size;
};
*/

void	*list_iter_while(List_p list, void *(f)(void *));
void	list_iter(List_p list, void (f)(void *));
void	insert_link_top(List_p *refHeadTop, List_p subLinkChain);
void	*remove_link_content(List_p *refHead, void *data);
void	*remove_link_top(List_p *refHeadTop);
void	*delete_link(List_p link);
void	*new_link(void *size, size_t content_size);
void	insert_link_bottom(List_p *refHeadTop, List_p subLinkChain);
void	delete_list(List_p *refHead, void(f)(void *));

#endif
