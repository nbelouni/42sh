/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:30:53 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/07 17:29:34 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			is_sequence(char *s, int *pivot, int *begin, int *end)
{
	int		next;

	next = 0;
	*pivot = find_pivot(s, *pivot + 1, '.');
	while (*pivot >= 0 && *begin >= 0 && *end >= 0)
	{
		if (s[*pivot + 1] == '.')
		{
			next = TRUE;
			*begin = find_begin(s, *pivot);
			*end = find_end(s, *pivot);
			if (*pivot > 0 && *begin >= 0 && *end > 0)
				break ;
		}
		else
			next = FALSE;
		*pivot = find_pivot(s, *pivot + 1, '.');
	}
	if (*pivot < 0 || *begin < 0 || *end < 0 || next == FALSE)
		return (FALSE);
	return (TRUE);
}

int			init_bg_end_type(char *s, int *begin, int *end)
{
	int		pivot;

	*begin = 0;
	*end = 0;
	pivot = 0;
	if (is_sequence(s, &pivot, begin, end) == FALSE)
		return (FALSE);
	return (which_sequence_type(s, *begin, *end, pivot));
}

t_token		*expand_word(t_token *head)
{
	t_token	*new;
	t_token	*final;
	t_token	*tmp;
	int		ret;
	t_exp	exp;

	tmp = head;
	final = NULL;
	while (tmp)
	{
		ret = find_exp(tmp->word, &exp);
		if (ret == FALSE)
			ret = find_sequence(tmp->word, &exp);
		if (ret == TRUE)
		{
			new = expand_text(&exp, tmp);
			clean_t_exp(&exp);
			final_tmp(&final, &tmp, new, &exp);
			clean_t_exp(&exp);
		}
		tmp = tmp->next;
	}
	return (final);
}

t_token		*replace_expansions(t_token *lst)
{
	t_token	*head;
	t_token	*final;
	int		lvl[2];

	lvl[0] = lst->bt_level;
	lvl[1] = lst->bc_level;
	if (!(head = ft_tokenew(lst->type, ft_strdup(lst->word), lvl)))
		return (NULL);
	final = expand_word(head);
	ft_tokendestroy(&head);
	return (final);
}
