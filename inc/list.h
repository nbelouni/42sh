/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 19:57:37 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/10 07:12:13 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "42sh.h"

# define PUSH(x, elem)	(insert_link_top(x, new_link(elem, sizeof(elem))))
# define TOP(x)			(x->content)
# define POP(x)			(delete_link(remove_link_top(x)))

typedef struct s_list *List_p;

void	*list_iter_while(t_list *list, void *(f)(void *));
void	list_iter(t_list *list, void (f)(void *));
void	insert_link_top(t_list **ref_head_top, t_list *sub_link_chain);
void	*remove_link_content(t_list **ref_head, void *data);
void	*remove_link_top(t_list **ref_head_top);
void	*delete_link(t_list *link);
void	*new_link(void *size, size_t content_size);
void	insert_link_bottom(t_list **ref_head_top, t_list *sub_link_chain);
void	delete_list(t_list **ref_head, void(f)(void *));
void	*list_get_nth(List_p list, uint32_t nth);

#endif
