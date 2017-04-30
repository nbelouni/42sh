/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bang3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 22:40:44 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/30 22:40:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char		*find_number(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '-')
		i += 1;
	if (!ft_isdigit(s[i]))
		return (NULL);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (ft_strsub(s, 0, i));
		i++;
	}
	if (s[i - 1] < '9' && s[i - 1] > '0')
		return (ft_strdup(s));
	return (NULL);
}

