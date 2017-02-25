/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:51:24 by alallema          #+#    #+#             */
/*   Updated: 2017/02/25 19:56:42 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Faut faire des check avant de trier la liste, pour l'instant on garde ca
*/

void	sort_list_token(t_token **list)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (elem->type == CMD && elem->n_string &&
		elem->string->flag == NO_QUOTE && elem->string->s[0] == '#')
		{
			elem->prev->next = NULL;
			ft_tokendestroy(&elem);
			return ;
		}
		if (elem->type == CMD && elem->prev && (elem->prev->type == CMD
		|| elem->prev->type == ARG))
			elem->type = ARG;
		elem = elem->next;
	}
}
