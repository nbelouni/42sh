/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:51:04 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 17:51:05 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	dup src in dst then return dst, if dst already exists, dst is being free
*/

char		*ft_free_and_dup(char *dst, char *src)
{
	if (dst && dst[0])
		ft_strdel(&dst);
	dst = ft_strdup(src);
	return (dst);
}
