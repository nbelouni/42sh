/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:36:56 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:38:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		init_t_exp(t_exp *exp)
{
	exp->first_word = NULL;
	exp->last_word = NULL;
	exp->poss = NULL;
	exp->n_poss = 0;
}

void		clean_t_exp(t_exp *exp)
{
	if (exp->first_word)
		ft_strdel(&(exp->first_word));
	if (exp->last_word)
		ft_strdel(&(exp->last_word));
	if (exp->poss)
		ft_tabdel_and_init(&(exp->poss));
}

char		**split_poss(char *s, int end, int *n_poss)
{
	char	**new;
	int		i;
	int		begin;
	int		len;

	*n_poss = find_n_poss(s, end);
	if (!(new = ft_memalloc(sizeof(char *) * (*n_poss + 1))))
		return (NULL);
	i = -1;
	begin = 0;
	while (++i < *n_poss)
	{
		len = find_len(s + begin, end);
		if (!(new[i] = ft_strsub(s, begin, len)))
		{
			if (!(new[i] = ft_strdup("")))
				return (NULL);
		}
		begin += len + 1;
		len = 0;
	}
	return (new);
}

int			is_exp(char *s, int *pivot, int *begin, int *end)
{
	*pivot = find_pivot(s, *pivot + 1, ',');
	while (*pivot >= 0 && *begin >= 0 && *end >= 0)
	{
		*begin = find_begin(s, *pivot);
		*end = find_end(s, *pivot);
		if (*pivot > 0 && *begin >= 0 && *end > 0)
			break ;
		*pivot = find_pivot(s, *pivot + 1, ',');
	}
	if (*pivot < 0 || *begin < 0 || *end < 0)
		return (FALSE);
	return (TRUE);
}

int			find_exp(char *s, t_exp *exp)
{
	int		begin;
	int		end;
	int		pivot;

	init_t_exp(exp);
	pivot = 0;
	begin = 0;
	end = 0;
	if (is_exp(s, &pivot, &begin, &end) == FALSE)
		return (FALSE);
	if (!(exp->first_word = ft_strsub(s, 0, begin)))
		return (FALSE);
	if (!(exp->last_word = ft_strsub(s, end + 1, ft_strlen(s) - end)))
		return (FALSE);
	if (!(exp->poss = split_poss(s + begin + 1, end, &(exp->n_poss))))
		return (FALSE);
	return (TRUE);
}
