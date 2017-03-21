/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 17:39:50 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/21 15:47:32 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *orig, const char *search, const char *replace)
{
	char	*ret;
	char	*ptr;
	size_t	ret_len;
	size_t	len_orig;
	size_t	len_search;

	if (search == NULL || search[0] == '\0')
		return (NULL);
	if ((ptr = ft_strstr(orig, search)) == NULL)
		return (NULL);
	len_search = ft_strlen(search);
	len_orig = ft_strlen(orig);
	ret_len = (len_orig - len_search) + ft_strlen(replace);
	if ((ret = ft_strnew(ret_len)) == NULL)
		return (NULL);
	ret = ft_strncpy(ret, orig, (len_orig - ft_strlen(ptr)));
	ret = (replace != NULL) ? ft_strcat(ret, replace) : ret;
	ret = ft_strcat(ret, &(orig[(len_orig - ft_strlen(ptr) + len_search)]));
	return (ret);
}
