/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 20:39:17 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/08 17:25:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	clean_elem(t_token **elem)
{
	if ((*elem)->word)
		free((*elem)->word);
	(*elem)->word = NULL;
	free(*elem);
	*elem = NULL;
}

int		can_expand(char *s)
{
	int			pivot;
	int			begin;
	int			end;

	if (!s)
		return (FALSE);
	pivot = 0;
	begin = 0;
	end = 0;
	if (is_exp(s, &pivot, &begin, &end) == TRUE ||
	is_sequence(s, &pivot, &begin, &end) == TRUE)
		return (TRUE);
	return (FALSE);
}

void	expand_args(t_token **list, t_token **elem)
{
	t_token		*tail;
	t_token		*tmp;
	t_token		*to_del;

	if (can_expand((*elem)->word) == TRUE && (tmp = replace_expansions(*elem)))
	{
		to_del = *elem;
		tail = tmp;
		while (tail->next)
			tail = tail->next;
		if (!(*elem)->prev)
			*list = tmp;
		else
		{
			(*elem)->prev->next = tmp;
			tmp->prev = (*elem)->prev;
		}
		tail->next = (*elem)->next;
		if ((*elem)->next)
			(*elem)->next->prev = tail;
		*elem = ((*elem)->prev) ? tail : *list;
		clean_elem(&to_del);
	}
}
