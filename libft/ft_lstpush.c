/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:23:58 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 15:27:36 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstpush(t_list **begin, t_list *new)
{
	t_list	*elem;

	elem = *begin;
	if (elem == NULL)
	{
		*begin = elem;
		return ;
	}
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->prev = elem;
}

