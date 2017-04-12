/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:51:24 by alallema          #+#    #+#             */
/*   Updated: 2017/04/12 12:31:31 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_find_fd(t_token *list)
{
	char	*s;

	s = NULL;
	if (list && list->word && !ft_atoi(list->word) &&
		ft_strcmp(list->word, "0") != 0)
	{
		free(list->word);
		list->word = NULL;
	}
}

/*
**Faut faire des check avant de trier la liste, pour l'instant on garde ca
*/

void	sort_list_token2(t_token **list, t_completion *completion, t_lst *hist)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (((elem->type > START && elem->type < AMP) || (elem->type > AND
		&& elem->type < DIR_L_AMP)) && elem->next && elem->next->type == CMD)
			elem->next->type = TARGET;
		if (elem->type == CMD && elem->prev && (elem->prev->type == CMD
		|| elem->prev->type == ARG))
			elem->type = ARG;
		if (elem->type == DL_DIR)
			here_doc(elem->next, completion, hist);
		if (!elem->prev || !is_dir_type(elem->prev->type))
			expand_args(list, &elem);
		elem = elem->next;
	}
	while ((*list) && (*list)->prev)
		(*list) = (*list)->prev;
	return ;
}

void	sort_list_token(t_token **list, t_completion *completion, t_lst *hist)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (elem->type == FD_IN)
			(ft_swap_in(&elem) ? *list : (*list = elem));
		if (is_dir_type(elem->type))
			ft_find_fd(elem);
		if (ISAMP(elem) && elem->next && check_error_out(elem->next))
			return ;
		if (((elem->type > START && elem->type < AMP) || (elem->type > AND
		&& elem->type < DIR_L_AMP)) && elem->next && elem->next->type == CMD)
			elem->next->type = TARGET;
		if (elem->type == TARGET && elem->next && NEXTISCMD(elem))
			check_target_place(&elem);
		if (elem->type == CMD && elem->prev && PREVISCMD(elem))
			elem->type = ARG;
		if (elem->type == DL_DIR)
			here_doc(elem->next, completion, hist);
		if (!elem->prev || !is_dir_type(elem->prev->type))
			expand_args(list, &elem);
		elem = elem->next;
	}
	return ;
}
