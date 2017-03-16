/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:30:53 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/16 21:04:40 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

typedef struct	s_exp
{
	char		*first_word;
	char		**poss;
	int			n_poss;
	char		*last_word;
}				t_exp;

int		is_end(char *s, int *i, char c);
int		is_begin(char *s, int *i, char c);

int			find_pivot(char *s, int begin)
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
		if (is_char(s, i, ','))
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
			if (lvl != 0)
				lvl--;
			else
				poss++;
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
	i =-1;
	begin = 0;
	while (++i < *n_poss)
	{
	PUT2("s + begin: ");PUT2(s + begin);X('\n');
		len = find_len(s + begin, end);
		if (!(new[i] = ft_strsub(s, begin, len)))	
		{
			if (!(new[i] = ft_strdup("")))
				return (NULL);
		}
		PUT2("new[i] : ");PUT2(new[i]);X('\n');
		begin += len + 1;
		len = 0;
	}
	return (new);
}

int			find_exp(char *s, t_exp *exp)
{
	int		begin;
	int		end;
	int		pivot;

	pivot = 0;
	exp->first_word = NULL;
	exp->last_word = NULL;
	exp->poss = NULL;
	while ((pivot = find_pivot(s, pivot + 1)) >= 0)
	{
///		PUT2("pivot : ");E(pivot);X('\n');
		if (pivot > 0)
		{
			begin = find_begin(s, pivot);
			end = find_end(s, pivot);
			PUT2("begin : ");E(begin);PUT2(", end : ");E(end);X('\n');
			if (begin >= 0 && end > 0)
			{
				if (begin < 0 || !(exp->first_word = ft_strsub(s, 0, begin)))
					return (FALSE);
				PUT2("exp->first_word : ");PUT2(exp->first_word);X('\n');
				if (!(exp->last_word = ft_strsub(s, end + 1, ft_strlen(s) - end)))
					return (FALSE);
				PUT2("exp->last_word : ");PUT2(exp->last_word);X('\n');
				if (!(exp->poss = split_poss(s + begin + 1, end, &(exp->n_poss))))
					return (FALSE);
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

t_token		*expand_text(t_exp *exp, t_token *lst)
{
	t_token	*new;
	int		lvl[2];
	int		i;
	char	*new_word;

	i = 0;
	new = NULL;
	while (i < exp->n_poss)
	{
		lvl[0] = lst->bt_level;
		lvl[1] = lst->bc_level;
		if (!(new_word = ft_strnew(ft_strlen(exp->first_word) + ft_strlen(exp->last_word) + ft_strlen(exp->poss[i]) + 1)))
			return (NULL);
		ft_multi_concat(new_word, exp->first_word, exp->poss[i], exp->last_word);
		PUT2("new_word : ");PUT2(new_word);X('\n');
		if (new)
			ft_tokenpush(&new, ft_tokenew(lst->type, new_word, lvl));
		else
			new = ft_tokenew(lst->type, new_word, lvl);
		i++;
	}
	return (new);
}

void		del_poss(char **array, int n_poss)
{
	int		i;

	i = 0;
	while (i < n_poss)
	{
		PUT2("array[i] : ");PUT2(array[i]);X('\n');
		if (array[i])
			ft_strdel(&(array[i]));
		i++;
	}
	free(array);
	array = NULL;
}

void		fill_final_tmp(t_token **final, t_token **curr, t_token *new, t_exp *exp)
{
	t_token *tmp;

	tmp = new;
	while (tmp)
	{
		if (find_exp(tmp->word, exp) == FALSE)
		{
			if (*final)
				ft_tokenpush(final, tmp);
			else
				*final = tmp;
			tmp = tmp->next;
			if (tmp)
			{
				tmp->prev->next = NULL;
				tmp->prev = NULL;
			}
		}
		else
		{
			ft_tokenpush(curr, tmp);
			tmp = tmp->next;
			if (tmp)
			{
				tmp->prev->next = NULL;
				tmp->prev = NULL;
			}
		}
		if (exp->first_word)
			ft_strdel(&(exp->first_word));
		if (exp->last_word)
			ft_strdel(&(exp->last_word));
		if (exp->poss)
			del_poss(exp->poss, exp->n_poss);
	}
	new = NULL;
}

t_token		*find_expansions(t_token *lst)
{
	t_token	*head;
	t_token	*final;
	t_token	*new;
	t_token	*tmp;
	int		lvl[2];

	lvl[0] = lst->bt_level;
	lvl[1] = lst->bc_level;
	if (!(head = ft_tokenew(lst->type, ft_strdup(lst->word), lvl)))
		return (NULL);
	tmp = head;
	final = NULL;
	while (tmp)
	{
		t_exp	exp;
		if (find_exp(tmp->word, &exp) == TRUE)
		{
			new = expand_text(&exp, tmp);
			PUT2("___________ NEW ____________");PUT2(NULL);X('\n');
			ft_print_token_list(&new);
			if (exp.first_word)
				ft_strdel(&(exp.first_word));
			if (exp.last_word)
				ft_strdel(&(exp.last_word));
			if (exp.poss)
			del_poss(exp.poss, exp.n_poss);
			fill_final_tmp(&final, &tmp, new, &exp);
			if (exp.first_word)
				ft_strdel(&(exp.first_word));
			if (exp.last_word)
				ft_strdel(&(exp.last_word));
			if (exp.poss)
			del_poss(exp.poss, exp.n_poss);

			PUT2("___________ FINAL ____________");PUT2(NULL);X('\n');
			ft_print_token_list(&final);
			PUT2("___________ TMP ____________");PUT2(NULL);X('\n');
			ft_print_token_list(&tmp);

		}
		tmp = tmp->next;
	}
	ft_tokendestroy(&head);
	return (NULL);
}
