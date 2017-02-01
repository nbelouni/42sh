/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 21:01:28 by nbelouni          #+#    #+#             */
/*   Updated: 2014/11/19 06:53:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (NULL);
	ft_memset(s, '\0', (size + 1));
	return (s);
}
