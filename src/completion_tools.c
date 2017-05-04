/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 22:40:47 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:19:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		find_word_begin(char *s, int pos)
{
	int	i;

	i = pos - 1;
	while (i >= 0)
	{
		if (is_separator(s, i) || is_redirection(s, i) ||
		is_space(s, i) || is_any_quote(s, i))
			return (i + 1);
		else if (i == 0)
			return (i);
		i--;
	}
	return (0);
}

int		find_word_end(char *s)
{
	int	i;

	i = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len();
	while (s[i])
	{
		if (is_separator(s, i) || is_redirection(s, i) ||
		is_space(s, i) || is_any_quote(s, i))
			return (i);
		i++;
	}
	return (i);
}

int		find_cplt(char *s, t_slist *ref, t_slist **lst, int len)
{
	t_slist		*tmp;
	int			n_lst;

	n_lst = 0;
	tmp = ref;
	while (tmp)
	{
		if (!ft_strncmp(tmp->s, s, len))
		{
			if (!*lst)
				*lst = tmp;
			n_lst++;
		}
		tmp = tmp->next;
	}
	return (n_lst);
}

int		count_sort_lst(t_slist *lst)
{
	t_slist		*tmp;
	int			len;

	tmp = lst;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int		max_len_sort_lst(t_slist *lst, int n)
{
	t_slist		*tmp;
	int			len;

	tmp = lst;
	len = 0;
	while (n && tmp)
	{
		if ((int)ft_strlen(tmp->s) > len)
			len = (int)ft_strlen(tmp->s);
		n--;
		tmp = tmp->next;
	}
	return (len);
}
