/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:15:26 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/16 18:05:08 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		supp_char(char *s, int i, int c)
{
	int	j;

	j = i;
	if (is_char(s, i, c))
	{
		while (j < (int)ft_strlen(s))
		{
			s[j] = s[j + 1];
			j++;
		}
		return (TRUE);
	}
	return (FALSE);
}

void	supp_squote(char *s, int *i, int *len)
{
	int		j;

	supp_char(s, *i, '\'');
	j = find_next_char(s, *i, '\'');
	supp_char(s, *i + j, '\'');
	*i += j;
	len -= 2;
}

void	supp_dquote(char *s, int *i, int *len)
{
	int		j;

	supp_char(s, *i, '"');
	j = find_next_char(s, *i, '"');
	j += *i;
	while (*i < j)
	{
		if (supp_char(s, *i, '\\'))
			j--;
		(*i)++;
	}
	supp_char(s, *i, '"');
	*len -= 2;
}

void	supp_quotes(char *s)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = (int)ft_strlen(s);
	while (i < len)
	{
		if (is_char(s, i, '\''))
			supp_squote(s, &i, &len);
		else if (is_char(s, i, '"'))
			supp_dquote(s, &i, &len);
		else if (s[i] == '\\')
		{
			j = i - 1;
			while (++j < (int)ft_strlen(s))
				s[j] = s[j + 1];
			i += 1;
			len -= 1;
		}
		else
			i++;
	}
}

int		init_begin_end(char *s, int *begin, int *end)
{
	*begin = find_next_char(s, 0, '$');
	if (*begin < 0 || *begin + 1 >= (int)ft_strlen(s))
		return (TRUE);
	*begin += 1;
	*end = find_next_char(s, *begin, ' ');
	if (*end == -1)
		*end = ft_strlen(s) - *begin;
	return (FALSE);
}

int		init_new_value(char *var_name, t_lst *env, char **new_value)
{
	t_elem	*tmp;

	if (!var_name)
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	tmp = ft_find_elem(var_name, env);
	*new_value = (tmp && tmp->value && tmp->value[0]) ? tmp->value : NULL;
	if (var_name)
		ft_strdel(&var_name);
	return (0);
}

int		replace_env_var(char **s, t_lst *env)
{
	char	*new_val;
	char	*new_s;
	int		bg;
	int		end;
	int		tmp_len;

	if (init_begin_end(*s, &bg, &end) == TRUE)
		return (TRUE);
	if (init_new_value(ft_strsub(*s, bg, end), env, &new_val) == ERR_EXIT)
		return (ERR_EXIT);
	if (!(new_s = ft_strnew(ft_strlen(*s) - end + ft_strlen(new_val))))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	ft_strncpy(new_s, *s, bg - 1);
	if (new_val)
		ft_strncpy(new_s + bg - 1, new_val, ft_strlen(new_val));
	tmp_len = ft_strlen(*s) - (bg + end);
	ft_strncpy(new_s + bg - 1 + ft_strlen(new_val), *s + bg + end, tmp_len);
	new_s[ft_strlen(*s) - (end) + ft_strlen(new_val)] = 0;
	if (*s)
	{
		ft_strdel(s);
		*s = new_s;
	}
	return (FALSE);
}

int		globb(t_token *lst, t_lst *env)
{
	int		i;
	int		ret;

	i = 0;
	ret = FALSE;
	while (ret == FALSE)
	{
		is_end(lst->word, &i, '\'');
		if ((ret = replace_env_var(&(lst->word), env)) == ERR_EXIT)
			return (ERR_EXIT);
		i++;
	}
	//	TEMPORAIRE
	regex(lst);
	//
	supp_quotes(lst->word);
	return (0);
}

/*
**	Faire ca apres avoir envoye les btquotes
*/
int		edit_cmd(t_token *list, t_lst *env)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (globb(tmp, env) == ERR_EXIT)
			return (ERR_EXIT);
		tmp = tmp->next;
	}
	return (0);
}
