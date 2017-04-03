/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:51:24 by alallema          #+#    #+#             */
/*   Updated: 2017/03/17 18:09:45 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	sort_list_token(t_token **list, t_completion *completion, t_lst *hist)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (elem->type == CMD && elem->prev && (elem->prev->type == CMD
		|| elem->prev->type == ARG))
			elem->type = ARG;
		if (elem->type == DL_DIR)
		{
			here_doc(elem->next, completion, hist);
		}
		if (!elem->prev || is_dir_type(elem->prev->type))
			expand_args(list, &elem);
		elem = elem->next;
	}
}
