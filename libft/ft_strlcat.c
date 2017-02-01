/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:12:47 by nbelouni          #+#    #+#             */
/*   Updated: 2015/01/01 19:03:09 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_strlcat(char *dst, const char *src, unsigned int size)
{
	unsigned int	len_dst;
	unsigned int	i;

	len_dst = ft_strlen(dst);
	i = 0;
	if (size >= len_dst)
	{
		while (len_dst < size - 1)
		{
			dst[len_dst] = src[i];
			len_dst++;
			i++;
		}
		dst[len_dst] = '\0';
		return (len_dst + ft_strlen(src) - i);
	}
	return (ft_strlen(src) + size);
}
