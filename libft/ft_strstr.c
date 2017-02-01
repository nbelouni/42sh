/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 18:21:02 by nbelouni          #+#    #+#             */
/*   Updated: 2014/12/30 22:34:14 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k] && s2[j] && s1[k] == s2[j])
			{
				j++;
				k++;
			}
			if (s2[j] == '\0')
				return ((char *)s1 + (k - j));
		}
		i++;
	}
	return (NULL);
}
