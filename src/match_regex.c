/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_regex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:03:44 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:05:31 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			is_same_char(char *s, char *rg, int *i_s, int *i_rg)
{
	while (can_skip_char(rg, *i_rg))
		*i_rg += 1;
	if (is_regex(rg, *i_rg) == FALSE)
	{
		if (rg[*i_rg] != s[*i_s])
			return (free_rg_and_return(&rg, FALSE));
		*i_rg += 1;
		*i_s += 1;
	}
	else if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, '?'))
	{
		if (!s[*i_s])
			return (free_rg_and_return(&rg, FALSE));
		*i_rg += 1;
		*i_s += 1;
	}
	while (can_skip_char(rg, *i_rg))
		*i_rg += 1;
	return (TRUE);
}

int			is_pool_char(char *s, char *rg, int *i_s, int *i_rg)
{
	if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, '['))
	{
		*i_rg += 1;
		while (rg[*i_rg])
		{
			is_end(rg, i_rg, '\'');
			is_end(rg, i_rg, '`');
			is_end(rg, i_rg, '"');
			if (is_char(rg, *i_rg, ']'))
				break ;
			else if (s[*i_s] == rg[*i_rg])
				break ;
			*i_rg += 1;
		}
		if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, ']'))
			return (free_rg_and_return(&rg, FALSE));
		*i_rg += find_next_char(rg, *i_rg, ']') + 1;
		(*i_s)++;
	}
	while (can_skip_char(rg, *i_rg))
		*i_rg += 1;
	return (TRUE);
}

int			is_next_pool_char(char *s, char *rg, int *i_s, int *i_rg)
{
	int	j;
	int	k;

	if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, '['))
	{
		if (*i_rg + find_next_char(rg, *i_rg, ']') == (int)ft_strlen(rg) - 1)
			*i_s = ft_strlen(s) - 1;
		k = *i_rg;
		while (rg[++k] && !is_char(rg, k, ']'))
		{
			j = *i_s - 1;
			while (s[++j])
			{
				if (s[j] == rg[k])
					break ;
			}
			if (s[j] == rg[k])
				break ;
		}
		if (s[j] != rg[k])
			return (free_rg_and_return(&rg, FALSE));
		*i_rg += find_next_char(rg, *i_rg, ']') + 1;
		*i_s = j + 1;
	}
	return (TRUE);
}

int			is_next_all_char(char *s, char **rg, int *i_s, int *i_rg)
{
	if (which_quotes(*rg, *i_rg) == NO_QUOTE && is_char(*rg, *i_rg, '*'))
	{
		while ((*rg)[*i_rg] && is_char((*rg), *i_rg, '*'))
			*i_rg += 1;
		while ((*rg)[*i_rg] && can_skip_char(*rg, *i_rg))
			*i_rg += 1;
		if (!(*rg)[*i_rg])
		{
			*i_s = ft_strlen(s);
			return (free_rg_and_return(rg, TRUE));
		}
		if (find_next_char((*rg), *i_rg, '*') < 0)
			*i_s = ft_strlen(s) - find_last_len((*rg) + *i_rg);
		*i_s = (*i_s < 0) ? 0 : *i_s;
		if (!is_regex((*rg), *i_rg))
		{
			while (s[*i_s] && s[*i_s] != (*rg)[*i_rg])
				*i_s += 1;
			if (!s[*i_s])
				return (free_rg_and_return(rg, FALSE));
		}
		else if (is_next_pool_char(s, *rg, i_s, i_rg) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int			match_regex(char *s, char *rg_ref)
{
	int		i_s;
	int		i_rg;
	char	*rg;

	i_s = 0;
	i_rg = 0;
	if (!(rg = ft_strdup(rg_ref)))
		return (FALSE);
	if (rg_ref[ft_strlen(rg_ref) - 1] == '/')
		rg[ft_strlen(rg) - 1] = 0;
	while (i_s < (int)ft_strlen(s) && i_rg < (int)ft_strlen(rg))
	{
		if (is_same_char(s, rg, &i_s, &i_rg) == FALSE ||
		is_pool_char(s, rg, &i_s, &i_rg) == FALSE ||
		is_next_all_char(s, &rg, &i_s, &i_rg) == FALSE)
			return (FALSE);
		if (rg == NULL)
			return (TRUE);
	}
	while (rg[i_rg] && rg[i_rg] == '*')
		i_rg += 1;
	if (i_s < (int)ft_strlen(s) || i_rg < (int)ft_strlen(rg))
		return (free_rg_and_return(&rg, FALSE));
	return (free_rg_and_return(&rg, TRUE));
}
