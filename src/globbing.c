/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:15:26 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 13:40:32 by nbelouni         ###   ########.fr       */
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
		if (s[*i + 1] && (s[*i + 1] == '$' || s[*i + 1] == '\\' ||
		s[*i + 1] == '`' || s[*i + 1] == '"'))
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
	int		i;

	*begin = find_next_char(s, 0, '$');
	if (*begin < 0 || *begin + 1 >= (int)ft_strlen(s) ||
	which_quotes(s, *begin) == S_QUOTE)
		return (TRUE);
	*begin += 1;
	i = *begin;
	*end = 0;
	while (s[i + *end] && ft_isalnum(s[i + *end]))
		*end += 1;
	return (FALSE);
}

int		init_new_value(char *var_name, t_core *core, char **new_value)
{
	t_elem	*tmp;

	if (!var_name)
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(tmp = ft_find_elem(var_name, core->set)))
	{
		if (!(tmp = ft_find_elem(var_name, core->env)))
			tmp = ft_find_elem(var_name, core->exp);
	}
	*new_value = (tmp && tmp->value && tmp->value[0]) ? tmp->value : NULL;
	if (var_name)
		ft_strdel(&var_name);
	return (0);
}

int		replace_env_var(char **s, t_core *core)
{
	char	*new_val;
	char	*new_s;
	int		bg;
	int		end;
	int		tmp_len;

	if (init_begin_end(*s, &bg, &end) == TRUE)
		return (TRUE);
	if (init_new_value(ft_strsub(*s, bg, end), core, &new_val) == ERR_EXIT)
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

int		insert_new_args(char **s, t_reg_path **new_args, t_reg_path *tmp)
{
	t_reg_path	*tmp2;

	if (*new_args)
	{
		tmp2 = *new_args;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
		tmp->prev = tmp2;
	}
	else
		*new_args = tmp;
	ft_strdel(s);
	if (!(*s = ft_strdup("")))
		return (FALSE);
	tmp2 = tmp;
	while (tmp2)
	{
		supp_quotes(*s);
		tmp2 = tmp2->next;
	}
	return (TRUE);
}

int		globb(char **s, t_core *core, t_reg_path **new_args)
{
	int			i;
	int			ret;
	t_reg_path	*tmp;

	i = 0;
	ret = FALSE;
	while (ret == FALSE)
	{
		is_end(*s, &i, '\'');
		if ((ret = replace_env_var(s, core)) == ERR_EXIT)
			return (ERR_EXIT);
		i++;
	}
	if ((tmp = replace_regex(*s)))
	{
		if (insert_new_args(s, new_args, tmp) == FALSE)
			return (FALSE);
	}
	else
		supp_quotes(*s);
	return (TRUE);
}

int		args_len(char **args, t_reg_path *reg_args)
{
	int			len;
	int			i;
	t_reg_path	*tmp;

	i = -1;
	len = 0;
	while (args[++i])
	{
		if (args[i][0])
			len += 1;
	}
	tmp = reg_args;
	while (tmp)
	{
		len += 1;
		tmp = tmp->next;
	}
	return (len);
}

char	**add_in_args(char **args, t_reg_path *reg_args)
{
	t_reg_path	*tmp;
	char		**new;
	int			i;
	int			j;

	if (!reg_args)
		return (args);
	if (!(new = ft_memalloc(sizeof(char *) * (args_len(args, reg_args) + 1))))
		return (NULL);
	i = -1;
	j = -1;
	while (++i < (int)ft_tablen(args))
	{
		if (args[i][0])
			if (!(new[++j] = ft_strdup(args[i])))
				return (NULL);
	}
	tmp = reg_args;
	while (tmp)
	{
		if (!(new[++j] = ft_strdup(tmp->out)))
			return (NULL);
		tmp = tmp->next;
	}
	return (new);
}

int		edit_cmd(char ***args, t_core *core)
{
	t_reg_path	*new_args;
	char		**tmp;
	int			i;

	new_args = NULL;
	i = -1;
	while ((*args)[++i])
	{
		if (globb(&(*args)[i], core, &new_args) == ERR_EXIT)
			return (ERR_EXIT);
	}
	if (new_args)
	{
		if (!(tmp = add_in_args(*args, new_args)))
			return (ERR_EXIT);
		ft_tabdel(*args);
		*args = tmp;
		ft_reg_pathdestroy(&new_args);
	}
	return (0);
}
