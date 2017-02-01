/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 01:14:11 by nbelouni          #+#    #+#             */
/*   Updated: 2014/12/30 23:53:36 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			i;

	i = 0;
	if (!s)
	{
		if (!(new = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
	}
	else
	{
		if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
	}
	while (s && s[start] && i < len)
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
