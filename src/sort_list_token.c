/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:51:24 by alallema          #+#    #+#             */
/*   Updated: 2017/03/12 00:04:41 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_swap_in(t_token *list)
{
	char	*s;
	int		ret;

	ret = 2;
	if (list->next->type == DIR_AMP)
		ret = 3;
	s = ft_memalloc(ft_strlen(list->word) + ret);
	s = ft_strcpy(s, list->word);
	ft_memcpy(&s[ft_strlen(list->word)], list->next->word,
	ft_strlen(list->next->word));
	free(list->next->word);
	list->next->word = s;
	ft_tokenclear(&list);
}

/*
**	Faut faire des check avant de trier la liste, pour l'instant on garde ca
**	On oublie les commentaires, c'est beaucoup trop chiant
*/

void	sort_list_token(t_token **list, t_completion *completion)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (elem->type == FD_IN)
			ft_swap_in(elem);
/*
 ** ATTENTION VERIF DIR_AMP + num + alpha VERIF a faire
 */
		if (elem->type == FD_OUT)
			elem->type == CMD;
/*
 ** ATTENTION FAIRE DES VERIF AVANT !!!!
 */
		if (elem->type == CMD && elem->prev && (elem->prev->type == CMD
		|| elem->prev->type == ARG))
			elem->type = ARG;
		if (elem->type == DL_DIR)
		{
			here_doc(elem->next, completion);
		}
		elem = elem->next;
	}
}
