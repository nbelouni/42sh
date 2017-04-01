/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:19:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:19:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			find_pivot(char *s, int begin, char c)
{
	int		i;
	int		s_len;

	i = begin;
	s_len = ft_strlen(s);
	while (i < s_len)
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, c))
			return (i);
		i++;
	}
	return (-1);
}

int			find_begin(char *s, int pivot)
{
	int		i;
	int		lvl;

	i = pivot;
	lvl = 0;
	while (--i >= 0)
	{
		is_begin(s, &i, '\'');
		is_begin(s, &i, '`');
		is_begin(s, &i, '"');
		if (is_char(s, i, '}'))
			lvl++;
		if (is_char(s, i, '{'))
		{
			if (lvl > 0)
				lvl--;
			else
				return (i);
		}
	}
	return (-1);
}

int			find_end(char *s, int pivot)
{
	int		i;
	int		s_len;
	int		lvl;

	i = pivot;
	lvl = 0;
	s_len = ft_strlen(s);
	while (++i < s_len)
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '{'))
			lvl++;
		if (is_char(s, i, '}'))
		{
			if (lvl > 0)
				lvl--;
			else
				return (i);
		}
	}
	return (-1);
}

int			find_n_poss(char *s, int end)
{
	int		i;
	int		lvl;
	int		poss;

	i = -1;
	lvl = 0;
	poss = 0;
	while (++i < end)
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '{'))
			lvl++;
		if (is_char(s, i, '}'))
		{
			if (lvl == 0)
				poss++;
			lvl--;
		}
		if (is_char(s, i, ',') && lvl == 0)
			poss++;
	}
	return (poss);
}

int			find_len(char *s, int end)
{
	int		i;
	int		lvl;
	int		poss;

	i = -1;
	lvl = 0;
	poss = 0;
	while (++i < end)
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '{'))
			lvl++;
		if (is_char(s, i, '}'))
		{
			if (lvl != 0)
				lvl--;
			else
				return (i);
		}
		if (is_char(s, i, ',') && lvl == 0)
			return (i);
	}
	return (-1);
}
