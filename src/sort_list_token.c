/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:51:24 by alallema          #+#    #+#             */
/*   Updated: 2017/03/15 12:59:30 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	A check si pas de cmd avant token redir
*/

t_token	*move_for_token(t_token *elem)
{
	t_token	*tmp;
	t_token	*ret;

	tmp = elem->prev->prev;
	ret = elem->next;
	if (tmp && tmp->prev && (tmp->prev->type == CMD || tmp->prev->type == ARG))
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
	return (ret);
}

void	check_target_place(t_token *list)
{
	t_token	*elem;

	elem = list;
	elem = elem->next;
	while (elem && elem->type == CMD)
		elem = move_for_token(elem);
}

int		check_error_out(t_token *elem)
{
	int		i;

	i = 0;
	if (elem && elem->type == TARGET)
	{
		while (elem->word[i])
		{
			if (ft_isdigit(elem->word[i]) == 0)
				return (ERR_FD);
			i++;
		}
	}
	return (0);
}

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

int		sort_list_token(t_token **list, t_completion *completion)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (elem->type == FD_IN)
			ft_swap_in(elem);
		if (elem->type == DIR_AMP && elem->next && check_error_out(elem->next))
			return (ft_print_error(elem->word, ERR_FD_AMB, ERR_FD));
		if (((elem->type > START && elem->type < AMP) || (elem->type > AND
			&& elem->type < DIR_AMP)) && elem->next && elem->next->type == CMD)
			elem->next->type = TARGET;
		if (elem->type == TARGET)
			check_target_place(elem);
		if (elem->type == CMD && elem->prev && (elem->prev->type == CMD
		|| elem->prev->type == ARG))
			elem->type = ARG;
		if (elem->type == DL_DIR)
			here_doc(elem->next, completion);
		elem = elem->next;
	}
	return (0);
}
