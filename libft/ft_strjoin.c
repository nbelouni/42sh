/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 01:40:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/21 19:20:25 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_cpy(char *new, const char *s1, const char *s2)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (s1 && s1[j])
	{
		new[j] = s1[j];
		j++;
	}
	while (s2 && s2[k])
	{
		new[j] = s2[k];
		j++;
		k++;
	}
	return (j);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
	{
		if (!(new = (char *)malloc(sizeof(char) * ft_strlen(s2) + 1)))
			return (NULL);
	}
	else if (!s2)
	{
		if (!(new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
			return (NULL);
	}
	else
		new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	j = ft_cpy(new, s1, s2);
	new[j] = '\0';
	return (new);
}
