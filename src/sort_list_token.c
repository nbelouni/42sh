/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:51:24 by alallema          #+#    #+#             */
/*   Updated: 2017/03/01 22:33:23 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Faut faire des check avant de trier la liste, pour l'instant on garde ca
**	On oublie les commentaires, c'est beaucoup trop chiant
*/

void	sort_list_token(t_token **list)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (elem->type == CMD && elem->prev && (elem->prev->type == CMD
		|| elem->prev->type == ARG))
			elem->type = ARG;
		elem = elem->next;
	}
}
