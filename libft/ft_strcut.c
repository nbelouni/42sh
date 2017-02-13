/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 19:01:41 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/03 19:23:25 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *str, char c)
{
	char	*ret;

	ret = (str && str[0]) ? ft_strsub(str, 0, ft_get_index_of(str, c)) : NULL;
	return (ret);
}
