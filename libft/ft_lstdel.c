/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 08:35:15 by nbelouni          #+#    #+#             */
/*   Updated: 2014/11/18 00:02:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (alst && del)
	{
		tmp = *alst;
		while (*alst)
		{
			*alst = (*alst)->next;
			ft_lstdelone(&tmp, del);
			tmp = *alst;
		}
	}
}
