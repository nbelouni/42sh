/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_sequence_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:23:52 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:34:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			is_number(char *s, int len)
{
	int		i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i += 1;
	while (i < len)
	{
		if (s[i] > '9' || s[i] < '0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int			which_sequence_type(char *s, int begin, int end, int pivot)
{
	begin += 1;
	end -= 1;
	if (pivot - begin == 1 && end - pivot == 2)
	{
		if (ft_isalpha(s[begin]) && ft_isalpha(s[end]))
			return (ALPHA);
		if (is_number(s + begin, 1) && is_number(s + end, 1))
			return (NUMERIC);
	}
	else if (is_number(s + begin, pivot - begin) &&
	is_number(s + pivot + 2, end - (pivot + 2)))
		return (NUMERIC);
	return (NO_SQ_TYPE);
}

char		**iter_ascii_sq(char *first, char *last, int *len)
{
	char	**new;
	int		iter;
	int		i;

	*len = first[0] - last[0];
	if (*len < 0)
	{
		iter = 1;
		*len *= -1;
	}
	else
		iter = -1;
	if (!(new = ft_memalloc(sizeof(char *) * (*len + 2))))
		return (NULL);
	i = -1;
	while (++i <= *len)
	{
		new[i] = ft_strdup(first);
		first[0] += iter;
	}
	return (new);
}

char		**iter_num_sq(int first, int last, int *len)
{
	char	**new;
	int		iter;
	int		i;

	*len = first - last;
	if (*len < 0)
	{
		iter = 1;
		*len *= -1;
	}
	else
		iter = -1;
	if (!(new = ft_memalloc(sizeof(char *) * (*len + 2))))
		return (NULL);
	i = -1;
	while (++i <= *len)
	{
		new[i] = ft_itoa(first);
		first += iter;
	}
	return (new);
}

int			init_exp_sq(char **sq, int type, t_exp *exp)
{
	if (type == ALPHA)
		exp->poss = iter_ascii_sq(sq[0], sq[1], &(exp->n_poss));
	else if (type == NUMERIC)
		exp->poss = iter_num_sq(ft_atoi(sq[0]), ft_atoi(sq[1]), &(exp->n_poss));
	else
	{
		ft_tabdel_and_init(&sq);
		return (FALSE);
	}
	return (TRUE);
}
