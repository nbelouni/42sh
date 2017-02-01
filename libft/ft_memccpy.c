/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 02:37:21 by nbelouni          #+#    #+#             */
/*   Updated: 2014/11/18 01:15:04 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n > 0)
	{
		d[i] = s[i];
		if ((unsigned char)c == s[i])
		{
			d[i] = (unsigned char)c;
			return ((void *)d + i + 1);
		}
		n--;
		i++;
	}
	return (NULL);
}
