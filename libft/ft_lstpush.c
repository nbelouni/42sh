/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 11:14:43 by alallema          #+#    #+#             */
/*   Updated: 2017/03/16 13:13:22 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list **begin, void const *s, size_t s_size)
{
	t_list	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	if (!elem->next)
	{
		elem->next = ft_lstnew(s, s_size);
		return ;
	}
	else
		elem->next = ft_lstnew(s, s_size);
	return ;
}
