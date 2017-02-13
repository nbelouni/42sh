/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epurstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:19:35 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/07 18:19:37 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_epurstr(char *str)
{
	char	*tmp;
	char	*ret;
	int		i;
	int		j;

	if ((tmp = ft_strnew(ft_strlen(str))) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		tmp[j] = (str[i]) ? ' ' : '\0';
		j++;
	}
	ret = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (ret);
}
