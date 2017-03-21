/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_regex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 16:24:49 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/20 18:32:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		is_regex_in_text(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (is_char(s, i, '?') || is_char(s, i, '*'))
			return (TRUE);
		else if (is_char(s, i, '[') && find_next_char(s, i + 1, ']') >= 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		count_slashs(char *s)
{
	int	i;
	int	n_slash;

	i = -1;
	n_slash = 0;
	while (s[++i])
	{
		if (is_char(s, i, '/'))
			n_slash++;
	}
	return (n_slash);
}

int		regex(t_token *lst)
{
	t_reg_paths	*all_paths;
	t_reg_paths	*tmp;
	char		**split_path;
	char		*join;
	int			all_paths_len;
	int			curr_dir;;
	int			i;

	all_paths_len = count_slashs(lst->word);
	if (!(all_paths = ft_memalloc(sizeof(t_reg_paths))))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (lst->word[0] == '/')
	{
		if (!(all_paths->path = ft_strdup("/")))
			return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	}
	else if (!(all_paths->path = getcwd(NULL, 1024)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(split_path = ft_strsplit(lst->word, '/')))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	i = -1;
	curr_dir = 0;
	tmp = all_paths;
	while (split_path[++i])
	{
		if (is_regex_in_text(split_path[i]) == FALSE)
		{
			if (!(tmp->match = ft_memalloc(sizeof(t_reg_paths))))
				return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
			if (!(join = ft_strjoin(tmp->path, "/")))
				return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
			if (!(tmp->match->path = ft_strjoin(join, split_path[i])))
				return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
			ft_strdel(&join);
		}
		else
		{
			PUT2("REGEXP IN TEXT");PUT2(NULL);X('\n');
		}
		tmp = tmp->match;
	}
	tmp = all_paths;
	while (tmp)
	{
		t_reg_paths *tmp2 = tmp->match;
		PUT2("____________________________\nPATH : ");PUT2(tmp->path);X('\n');
		while (tmp2)
		{
			PUT2("MATCH : ");PUT2(tmp2->path);X('\n');
			tmp2 = tmp2->next;
		}
		tmp = tmp->match;
		
	}
	return (0);
}
