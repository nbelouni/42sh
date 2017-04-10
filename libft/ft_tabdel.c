/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:50:49 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/17 13:11:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabdel(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
	{
		ft_strdel(&tab[i]);
	}
	free(tab);
	tab = NULL;
}

void		ft_tabdel_and_init(char ***tab)
{
	int		i;

	i = -1;
	if (*tab)
	{
		while (tab[0][++i])
		{
			ft_strdel(&tab[0][i]);
		}
		free(*tab);
	}
	*tab = NULL;
}
