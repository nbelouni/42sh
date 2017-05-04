/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:14:26 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:14:32 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_char_replace(char *s, char search, char replace)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == search)
			s[i] = replace;
	}
	return (0);
}
