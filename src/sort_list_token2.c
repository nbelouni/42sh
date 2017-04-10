/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 20:40:53 by alallema          #+#    #+#             */
/*   Updated: 2017/04/08 21:09:03 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** A check si pas de cmd avant token redir
*/

static void		move_elem(t_token *tmp, t_token *elem, t_token *ret)
{
	if (tmp && tmp->prev)
	{
		tmp = tmp->prev;
		elem->prev->next = elem->next;
		if (elem->next)
			elem->next->prev = elem->prev;
		elem->next = tmp->next;
		tmp->next = elem;
		elem->prev = tmp;
		if (elem->next)
			elem->next->prev = elem;
		elem->type = ARG;
	}
	else if (tmp && !tmp->prev)
	{
		if (ret)
			ret->prev = elem->prev;
		elem->prev->next = elem->next;
		elem->next = tmp;
		tmp->prev = elem;
		elem->prev = NULL;
		elem->type = CMD;
	}
}

static t_token	*move_for_token(t_token *elem)
{
	t_token	*tmp;
	t_token	*ret;

	tmp = elem->prev;
	while (tmp->prev && (tmp->type == TARGET || is_dir_type(tmp->type)))
		tmp = tmp->prev;
	if (!is_dir_type(tmp->type))
		tmp = tmp->next;
	ret = elem->next;
	move_elem(tmp, elem, ret);
	return (ret);
}

void			check_target_place(t_token **list)
{
	t_token	*elem;

	elem = *list;
	elem = elem->next;
	while (elem && elem->prev && elem->type == CMD)
		elem = move_for_token(elem);
	if (elem && !elem->prev)
		*list = elem;
}

int				check_error_out(t_token *elem)
{
	int		i;

	i = 0;
	if (elem && elem->type == TARGET)
	{
		if (elem->word[0] == '-')
			return (0);
		while (elem->word[i])
		{
			if (ft_isdigit(elem->word[i]) == 0)
				return (ERR_FD);
			i++;
		}
	}
	return (0);
}

int				ft_swap_in(t_token **list)
{
	t_token		*tmp;

	tmp = (*list);
	if (tmp && tmp->next && tmp->next->word)
		free(tmp->next->word);
	(*list)->next->word = (*list)->word;
	tmp = (*list)->next;
	ft_tokenclear(list);
	(*list) = tmp;
	if (*list && !(*list)->prev)
		return (0);
	return (1);
}
