/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_regex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:08:34 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:12:23 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			insert_in_next(t_reg_path *c, t_reg_path **next, char *d_name)
{
	char			*t;
	char			*np;
	char			*no;

	t = ft_strcmp(c->path, "/") ? ft_strjoin(c->path, "/") : ft_strdup(c->path);
	if (!(np = ft_strjoin(t, d_name)))
		return (ft_print_error("42sh : ", ERR_MALLOC, ERR_EXIT));
	ft_strdel(&t);
	if (c->is_abs == FALSE)
	{
		t = (c->out) ? ft_strjoin(c->out, "/") : NULL;
		no = ft_strjoin(t, d_name);
		ft_strdel(&t);
	}
	else
		no = ft_strdup(np);
	if (*next == NULL)
	{
		if (!(*next = ft_reg_pathnew(np, no, c->level + 1, c->is_abs)))
			return (ft_print_error("42sh : ", ERR_MALLOC, ERR_EXIT));
	}
	else
		ft_reg_pathadd(next, ft_reg_pathnew(np, no, c->level + 1, c->is_abs));
	return (TRUE);
}

int			keep_path(t_reg_path *curr, char *rg, t_reg_path **next_path)
{
	DIR				*dirp;
	struct dirent	*dp;

	if ((dirp = opendir(curr->path)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
		{
			if ((rg[0] != '.' && dp->d_name[0] != '.') ||
			(rg[0] == '.' && dp->d_name[0] == '.'))
			{
				if (is_regex_in_text(rg) == FALSE)
				{
					if (!ft_strncmp(dp->d_name, rg, ft_strlen(rg) - 1))
						insert_in_next(curr, next_path, dp->d_name);
				}
				else if (match_regex(dp->d_name, rg) == TRUE)
					insert_in_next(curr, next_path, dp->d_name);
			}
		}
		closedir(dirp);
	}
	else
		return (FALSE);
	return (TRUE);
}

void		dispach(t_reg_path *tmp, t_reg_path **nx, t_reg_path **f, int lvl)
{
	while (tmp)
	{
		if ((tmp)->level == lvl)
		{
			if (*f)
				ft_reg_pathpush(f, tmp);
			else
				*f = tmp;
		}
		else
		{
			if (*nx)
				ft_reg_pathpush(nx, tmp);
			else
				*nx = tmp;
		}
		tmp = (tmp)->next;
		if (tmp)
		{
			(tmp)->prev->next = NULL;
			(tmp)->prev = NULL;
		}
	}
}

int			find_regex(t_reg_path **curr, t_reg_path **final, char *rg, int len)
{
	t_reg_path	*tmp;
	t_reg_path	*next_paths;

	next_paths = NULL;
	while (*curr)
	{
		keep_path(*curr, rg, &next_paths);
		tmp = *curr;
		*curr = (*curr)->next;
		ft_strdel(&(tmp->path));
		ft_strdel(&(tmp->out));
		free(tmp);
	}
	tmp = next_paths;
	next_paths = NULL;
	dispach(tmp, &next_paths, final, len);
	*curr = next_paths;
	next_paths = NULL;
	return (TRUE);
}
