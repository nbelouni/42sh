/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 18:15:50 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 18:22:04 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		count_prev_char(char *s, int i, char c)
{
	int len;

	len = 0;
	while (i - len >= 0 && s[i - len] == c)
	{
		len += 1;
	}
	return (len);
}

int		is_char(char *s, int i, char c)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

int		find_prev_char(char *s, int len, char c)
{
	int		i;

	i = 0;
	while (len - i > 0)
	{
		if (is_char(s, len - i, c))
			return (i);
		i++;
	}
	return (0);
}

int		find_next_char(char *s, int len, char c)
{
	int		i;

	i = 0;
	while (len + i < (int)ft_strlen(s))
	{
		if (is_char(s, len + i, c))
			return (i);
		i++;
	}
	return (-1);
}
