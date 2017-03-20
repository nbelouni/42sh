/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:30:53 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/20 18:00:55 by nbelouni         ###   ########.fr       */
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

	i = 0;
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

t_token		*find_expansions(t_token *lst)
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
