/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:30:53 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/17 16:29:36 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

enum			e_reg_type
{
	SEQUENCE,
	LIST
};

typedef struct	s_exp
{
	char		*first_word;
	char		**poss;
	int			n_poss;
	char		*last_word;
	int			type;
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

//	PUT2("2 n_poss : ");E(*n_poss);X('\n');
	if (!(new = ft_memalloc(sizeof(char *) * (*n_poss + 1))))
		return (NULL);
	i =-1;
	begin = 0;
	while (++i < *n_poss)
	{
//		PUT2("s + begin: ");PUT2(s + begin);X('\n');
		len = find_len(s + begin, end);
		if (!(new[i] = ft_strsub(s, begin, len)))	
		{
			if (!(new[i] = ft_strdup("")))
				return (NULL);
		}
//		PUT2("new[i] : ");PUT2(new[i]);X('\n');
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
	exp->n_poss = 0;
	while ((pivot = find_pivot(s, pivot + 1)) >= 0)
	{
		///		PUT2("pivot : ");E(pivot);X('\n');
		if (pivot > 0)
		{
			begin = find_begin(s, pivot);
			end = find_end(s, pivot);
//			PUT2("begin : ");E(begin);PUT2(", end : ");E(end);X('\n');
			if (begin >= 0 && end > 0)
			{
				if (begin < 0 || !(exp->first_word = ft_strsub(s, 0, begin)))
					return (FALSE);
//				PUT2("exp->first_word : ");PUT2(exp->first_word);X('\n');
				if (!(exp->last_word = ft_strsub(s, end + 1, ft_strlen(s) - end)))
					return (FALSE);
//				PUT2("exp->last_word : ");PUT2(exp->last_word);X('\n');
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
//		PUT2("new_word : ");PUT2(new_word);X('\n');
		if (new)
			ft_tokenpush(&new, ft_tokenew(lst->type, new_word, lvl));
		else
			new = ft_tokenew(lst->type, new_word, lvl);
		i++;
	}
	return (new);
}

int			is_number(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i += 1;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char		**iter_ascii_sequence(char *first, char *last)
{
	char	**new;
	int		len;
	int		iter;
	int		i;

	len = first[0] - last[0];
	if (len < 0)
	{
		iter = 1;
		len *= -1;
	}
	else
		iter = -1;
	if (!(new = ft_memalloc(sizeof(char *) * (len + 2))))
		return (NULL);
	i = -1;
	while (++i <= len)
	{
		new[i] = ft_strdup(first);
		first[0] += iter;
	}
	i = -1;
	while (new[++i])
	{
//		PUT2("new[i] : ");PUT2(new[i]);X('\n');
	}
	return (new);

}

char		**iter_num_sequence(int first, int last)
{
	char	**new;
	int		len;
	int		iter;
	int		i;

	len = first - last;
	if (len < 0)
	{
		iter = 1;
		len *= -1;
	}
	else
		iter = -1;
	if (!(new = ft_memalloc(sizeof(char *) * (len + 2))))
		return (NULL);
	i = -1;
	while (++i <= len)
	{
		new[i] = ft_itoa(first);
		first += iter;
	}
	i = -1;
	while (new[++i])
	{
//		PUT2("new[i] : ");PUT2(new[i]);X('\n');
	}
	return (new);

}

int			find_sequence(char *s, t_exp *exp)
{
	int		begin;
	int		end;
	char	**sequence;
	char	*tmp;

	(void)exp;
	begin = find_next_char(s, 0, '{');
	end = find_next_char(s, begin, '}');
	if (begin < 0 || end < 0)
		return (FALSE);
	if (!(tmp = ft_strsub(s, begin + 1, end - 1)))
		return (FALSE);
	if (!ft_strstr(tmp, ".."))
	{
		ft_strdel(&tmp);
		return (FALSE);
	}
	if (!(sequence = ft_strsplit(tmp, '.')))
	{
		ft_strdel(&tmp);
		return (FALSE);
	}
	if (ft_tablen(sequence) != 2)
	{
		ft_tabdel_and_init(&sequence);
		ft_strdel(&tmp);
		return (FALSE);
	}
	if (ft_strlen(sequence[0]) == 1 && ft_isalpha(sequence[0][0]) &&
		ft_strlen(sequence[1]) == 1 && ft_isalpha(sequence[1][0]))
	{
		exp->poss = iter_ascii_sequence(sequence[0], sequence[1]);
		exp->n_poss = ft_tablen(exp->poss);
	}
	else if (is_number(sequence[0]) && is_number(sequence[1]))
	{
		exp->poss = iter_num_sequence(ft_atoi(sequence[0]), ft_atoi(sequence[1]));
		exp->n_poss = ft_tablen(exp->poss);
	}
	else
	{
		ft_tabdel_and_init(&sequence);
		ft_strdel(&tmp);
		return (FALSE);
	}
	if (begin < 0 || !(exp->first_word = ft_strsub(s, 0, begin)))
		return (FALSE);
//	PUT2("exp->first_word : ");PUT2(exp->first_word);X('\n');
	if (!(exp->last_word = ft_strsub(s, begin + end + 1, ft_strlen(s) - end)))
		return (FALSE);
	ft_tabdel_and_init(&sequence);
	ft_strdel(&tmp);
//	PUT2("exp->last_word : ");PUT2(exp->last_word);X('\n');
//	PUT2("tout va bien\n");
	return (TRUE);
}

void		fill_final_tmp(t_token **final, t_token **curr, t_token *new, t_exp *exp)
{
	t_token *tmp;

	tmp = new;
	while (tmp)
	{
		if (find_exp(tmp->word, exp) == FALSE && find_sequence(tmp->word, exp) == FALSE)
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
		{
			ft_tabdel_and_init(&(exp->poss));
			exp->poss = NULL;
		}
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
		int ret = find_exp(tmp->word, &exp);
		if (ret == FALSE)
			ret = find_sequence(tmp->word, &exp);
		if (ret == TRUE)
		{
			new = expand_text(&exp, tmp);
//			PUT2("___________ NEW ____________");PUT2(NULL);X('\n');
//			ft_print_token_list(&new);
			if (exp.first_word)
				ft_strdel(&(exp.first_word));
			if (exp.last_word)
				ft_strdel(&(exp.last_word));
			if (exp.poss)
			{
				ft_tabdel_and_init(&(exp.poss));
				exp.poss = NULL;
			}
			fill_final_tmp(&final, &tmp, new, &exp);
			if (exp.first_word)
				ft_strdel(&(exp.first_word));
			if (exp.last_word)
				ft_strdel(&(exp.last_word));
			if (exp.poss)
			{
				ft_tabdel_and_init(&(exp.poss));
				exp.poss = NULL;
			}
//			PUT2("___________ TMP ____________");PUT2(NULL);X('\n');
//			ft_print_token_list(&tmp);

		}
		tmp = tmp->next;
	}
	ft_tokendestroy(&head);
			PUT2("___________ FINAL ____________");PUT2(NULL);X('\n');
			ft_print_token_list(&final);
	ft_tokendestroy(&final);
	return (NULL);
}
