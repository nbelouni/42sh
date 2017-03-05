/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:02:54 by alallema          #+#    #+#             */
/*   Updated: 2017/03/02 22:22:05 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		cut_space(char *s, int i)
{
	while (is_space(s, i) == ESPACE)
		i++;
	return (i);
}

int		is_brace(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '{' && ((!s[i + 1] || s[i + 1] == ' ') &&
		((i == 0 || is_separator(s, i - 1) || s[i - 1] == ' '
		|| s[i - 1] == '('))))
			return (O_BRACE);
		if (s[i] == '}')
		{
			if ((i == 0 || is_separator(s, i - 1) || s[i - 1] == ' ')
			&& (i + 1 >= (int)ft_strlen(s) || is_separator(s, i + 1)
			|| s[i + 1] == ' ' || s[i + 1] == ')'))
				return (C_BRACE);
		}
	}
	return (0);
}

int		is_space(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == ' ')
			return (ESPACE);
	}
	return (0);
}

int		is_dot(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == ';')
			return (DOT);
	}
	return (0);
}
