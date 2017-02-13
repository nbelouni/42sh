/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 21:08:26 by alallema          #+#    #+#             */
/*   Updated: 2017/02/13 21:33:43 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_cmd	*ft_cmdnew(int token, char *cmd)
{
	t_cmd	*elem;

	if (!(elem = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	if (cmd == NULL)
	{
		elem->token = token;
		elem->s = NULL;
	}
	else
	{
		elem->s = cmd;
		elem->token = token;
	}
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
