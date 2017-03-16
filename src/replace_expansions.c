/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:30:53 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/14 16:35:33 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		init_is_quote(int *s2, int i, int *is_quotes, char c)
{
	if (*is_quotes == c)
		*is_quotes = 0;
	else if (*is_quotes == 0)
	{
		*is_quotes = c;
		s2[i] = *is_quotes;
	}
}

void		find_which_quote(char *s, int *s2, int i, int *is_quotes)
{
	if (is_char(s, i, '\''))
		init_is_quote(s2, i, is_quotes, '\'');
	if (is_char(s, i, '"'))
		init_is_quote(s2, i, is_quotes, '"');
	if (is_char(s, i, '`'))
		init_is_quote(s2, i, is_quotes, '`');
}

int			find_max_lvl(int *lex, int len)
{
	int	lvl;
	int	i;

	lvl = 0;
	i = -1;
	while (++i < len)
	{
		if (lvl < lex[i])
			lvl = lex[i];
	}
	return (lvl);
}

int			is_missing_comma(int *lex, int len, int max_lvl)
{
	int		comma_per_lvl[max_lvl];
	int		i;
	int		level;

	PUT2("ok\n");
	i = -1;
	while (++i < max_lvl)
		comma_per_lvl[i] = 0;
	i = -1;
	level = 0;
	while (++i < len)
	{
		if (lex[i] > 0)
			level = lex[i];
		if (lex[i] == -1)
			comma_per_lvl[level - 1] += 1;
	}
	i = max_lvl;
	while (--i >= 0)
	{
		if (comma_per_lvl[i] == 0)
			return (i + 1);
	}
	return (0);
}

void		init_lex(char *s, int *s2, int *level, int *curr_level)
{
	int		i;
	int		is_quotes;

	PUT2("init_lex()");PUT2(NULL);X('\n');
	i = -1;
	is_quotes = 0;
	while (s[++i])
	{
		if (is_quotes != 0)
			s2[i] = -1000;
		else
			s2[i] = *curr_level;
		if (is_quotes == 0 && is_char(s, i, '{'))
		{
			*curr_level += 1;
			s2[i] = *curr_level;
			if (*level < *curr_level)
				*level = *curr_level;
		}
		else if (is_quotes == 0 && is_char(s, i, '}'))
		{
			s2[i] = -*curr_level;
			*curr_level = (*curr_level == 0) ? 0 : *curr_level - 1;
		}
//		else if (is_quotes == 0 && is_char(s, i, ',') && *curr_level > 0)
//			s2[i] = -1;
		find_which_quote(s, s2, i, &is_quotes);
	}
	i = -1;
	while (++i < (int)ft_strlen(s))
	{
		E(s2[i]);X(' ');
	}
	X('\n');
}

int			*lex_text(char *s, int *level)
{
	int		*s2;
	int		curr_level;
	int		i;

	PUT2("lex_text()");PUT2(NULL);X('\n');
	if (!(s2 = ft_memalloc(sizeof(int) * (ft_strlen(s) + 1))))
		return (NULL);
	i = -1;
	while (++i < (int)ft_strlen(s))
		s2[i] = 0;
	curr_level = 0;
	init_lex(s, s2, level, &curr_level);

//	if (curr_level != 0)
//	{
//		i = -1;
//		while (++i < (int)ft_strlen(s))
//		{
//			if (s2[i] <= curr_level && s2[i] > 0)
//				s2[i] = 0;
//			else if (s2[i] > curr_level)
//				s2[i] -= curr_level;
//		}
//	}
//	int tmp_lvl = is_missing_comma(s2, ft_strlen(s), find_max_lvl(s2, ft_strlen(s)));
//	while (tmp_lvl != 0)
//	{
//		i = -1;
//		while (++i < (int)ft_strlen(s))
//		{
//			if (s2[i] > tmp_lvl)
//				s2[i] -= 1;
//			else if (s2[i] == tmp_lvl)
//				s2[i] = 0;
//		}
//		tmp_lvl = is_missing_comma(s2, ft_strlen(s), find_max_lvl(s2, ft_strlen(s)));
//		PUT2("tmp_lvl : ");E(tmp_lvl);X('\n');
//	}
	return (s2);
}

char		**find_expansions(char **s)
{
	int				*lex;
//	int				begin;
//	int				end;
//	char			**new_args;
	int				max_lvl;

	PUT2("find_expansions()");PUT2(NULL);X('\n');
	max_lvl = 0;
	lex = lex_text(*s, &max_lvl);
	return (NULL);
}
