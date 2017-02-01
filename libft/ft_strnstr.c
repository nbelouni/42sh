/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:44:56 by nbelouni          #+#    #+#             */
/*   Updated: 2014/11/18 01:21:24 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!ft_strlen(s2))
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i] && s2[j] && s1[i] == s2[j] && i < n)
			{
				j++;
				i++;
			}
			if (s2[j] == '\0')
				return ((char *)s1 + (i - j));
		}
		i++;
	}
	return (NULL);
}
