/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:40:02 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:40:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_token		*expand_text(t_exp *exp, t_token *lst)
{
	t_token	*new;
	int		lvl[2];
	int		i;
	char	*new_w;

	i = 0;
	new = NULL;
	while (i < exp->n_poss)
	{
		lvl[0] = lst->bt_level;
		lvl[1] = lst->bc_level;
		if (!(new_w = ft_strnew(ft_strlen(exp->first_word) +
		ft_strlen(exp->last_word) + ft_strlen(exp->poss[i]) + 1)))
			return (NULL);
		ft_multi_concat(new_w, exp->first_word, exp->poss[i], exp->last_word);
		if (new)
			ft_tokenpush(&new, ft_tokenew(lst->type, new_w, lvl));
		else
			new = ft_tokenew(lst->type, new_w, lvl);
		i++;
	}
	return (new);
}

int			find_sequence(char *s, t_exp *exp)
{
	int		begin;
	int		end;
	char	**sq;
	char	*tmp;
	int		type;

	if ((type = init_bg_end_type(s, &begin, &end)) == NO_SQ_TYPE)
		return (FALSE);
	if (!(tmp = ft_strsub(s, begin + 1, end - begin - 1)))
		return (FALSE);
	sq = ft_strsplit(tmp, '.');
	ft_strdel(&tmp);
	if (sq == NULL)
		return (FALSE);
	if (init_exp_sq(sq, type, exp) == FALSE)
		return (FALSE);
	exp->n_poss = ft_tablen(exp->poss);
	if (!(exp->first_word = ft_strsub(s, 0, begin)))
		return (FALSE);
	if (!(exp->last_word = ft_strsub(s, end + 1, ft_strlen(s) - end)))
		return (FALSE);
	ft_tabdel_and_init(&sq);
	return (TRUE);
}

void		final_tmp(t_token **final, t_token **curr, t_token *new, t_exp *exp)
{
	t_token *tmp;

	tmp = new;
	while (tmp)
	{
		if (can_expand(tmp->word) == FALSE)
		{
			if (*final)
				ft_tokenpush(final, tmp);
			else
				*final = tmp;
		}
		else
			ft_tokenpush(curr, tmp);
		tmp = tmp->next;
		if (tmp)
		{
			tmp->prev->next = NULL;
			tmp->prev = NULL;
		}
		clean_t_exp(exp);
	}
	new = NULL;
}
