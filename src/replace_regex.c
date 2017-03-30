/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_regex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 16:24:49 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 09:01:57 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		is_regex_in_text(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '?') || is_char(s, i, '*'))
			return (TRUE);
		else if (is_char(s, i, '['))
		{
			is_end(s, &i, '\'');
			is_end(s, &i, '`');
			is_end(s, &i, '"');
			if (find_next_char(s, i + 1, ']') >= 0)
				return (TRUE);
		}
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
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '/'))
			n_slash++;
	}
	if (s[0] != '/')
		n_slash++;
	return (n_slash);
}

char		**split_args(char *s)
{
	char	**new;
	int		i;
	int		len;
	int		begin;
	int		end;

	len = count_slashs(s);

	if (!(new = ft_memalloc(sizeof(char *) * (len + 1))))
		return (NULL);
	if (s[0] == '/')
		begin = 1;
	else
		begin = 0;
	end = 0;
	i = -1;
	while (++i < len)
	{
		is_end(s, &end, '\'');
		is_end(s, &end, '`');
		is_end(s, &end, '"');
		if (find_next_char(s, begin, '/') >= 0)
			end += find_next_char(s, begin, '/');
		else
			end = ft_strlen(s) - begin;
		if (!(new[i] = ft_strsub(s, begin, end + 1)))
			return (NULL);
		begin += end + 1;
	}
	new[len] = NULL;
	return (new);
}

t_reg_path	*init_curr_path(char *s)
{
	char		*path;
	char		*out;
	t_bool		is_abs;

	if (s[0] == '/')
	{
		if (!(path = ft_strdup("/")))
			return (NULL);
		if (!(out = ft_strdup(path)))
			return (NULL);
		is_abs = TRUE;
	}
	else
	{
		if (!(path = getcwd(NULL, 1024)))
			return (NULL);
		out = NULL;
		is_abs = FALSE;
	}
	return (ft_reg_pathnew(path, out, 0, is_abs));
}

int			which_quotes(char *s, int len)
{
	int		w_quotes;
	int		i;

	w_quotes = 0;
	i = -1;
	while (++i < len)
	{
		if (is_char(s, i, '"'))
			w_quotes = (w_quotes == NO_QUOTE) ? D_QUOTE : NO_QUOTE;
		if (is_char(s, i, '\''))
			w_quotes = (w_quotes == NO_QUOTE) ? S_QUOTE : NO_QUOTE;
		if (is_char(s, i, '`'))
			w_quotes = (w_quotes == NO_QUOTE) ? BT_QUOTE : NO_QUOTE;
	}
	return (w_quotes);
}

int			is_regex(char *s, int i)
{
//	int len;
//	PUT2("s + i : ");PUT2(s + i);X('\n');
//	if ((len = which_quotes(s, i)) == 0)
	if (which_quotes(s, i) == NO_QUOTE)
	{
//	PUT2("len : ");E(len);X('\n');
		if (is_char(s, i, '?') || is_char(s, i, '*'))
			return (TRUE);
		if (is_char(s, i, '['))
		{
			while (i < (int)ft_strlen(s) && !is_char(s, i, ']'))
			{
				is_end(s, &i, '\'');
				is_end(s, &i, '`');
				is_end(s, &i, '"');
				i++;
			}
			if (i < (int)ft_strlen(s))
				return (TRUE);
		}
	}
	//PUT2("len : ");E(len);X('\n');
	return (FALSE);
}

int			find_last_len(char *s)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (++i < (int)ft_strlen(s))
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '['))
		{
			while (++i < (int)ft_strlen(s))
			{
				is_end(s, &i, '\'');
				is_end(s, &i, '`');
				is_end(s, &i, '"');
				if (is_char(s, i, ']'))
					break ;
			}
		}
		len++;
	}
	return (len);
}

int			free_rg_and_return(char *rg, int ret)
{
	if (rg && rg[0])
	{
		ft_bzero(rg, ft_strlen(rg));
		ft_strdel(&rg);
	}
	return (ret);
}

int			is_same_char(char *s, char *rg, int *i_s, int *i_rg)
{
	if (is_regex(rg, *i_rg) == FALSE)
	{
//		PUT2("rg + i_rg : ");PUT2(rg + *i_rg);X('\n');
//		PUT2("s + i_s : ");PUT2(s + *i_s);X('\n');
//		PUT2("REGEX : FALSE\n");
		if (rg[*i_rg] != s[*i_s])
			return (free_rg_and_return(rg, FALSE));
		*i_rg += 1;
		*i_s += 1;
	}
	else if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, '?'))
	{
		if (!s[*i_s])
			return (free_rg_and_return(rg, FALSE));
		*i_rg += 1;
		*i_s += 1;
	}
	return (TRUE);
}

int			is_pool_char(char *s, char *rg, int *i_s, int *i_rg)
{
	if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, '['))
	{
		*i_rg += 1;
		while (rg[*i_rg])
		{
			is_end(rg, i_rg, '\'');
			is_end(rg, i_rg, '`');
			is_end(rg, i_rg, '"');
			if (is_char(rg, *i_rg, ']'))
				break ;
			else if (s[*i_s] == rg[*i_rg])
				break ;
			*i_rg += 1;
		}
		if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, ']'))
			return (free_rg_and_return(rg, FALSE));
		*i_rg += find_next_char(rg, *i_rg, ']') + 1;
		(*i_s)++;
	}
	return (TRUE);
}

int			is_next_pool_char(char *s, char *rg, int *i_s, int *i_rg)
{
	int	j;
	int	k;

	if (which_quotes(rg, *i_rg) == NO_QUOTE && is_char(rg, *i_rg, '['))
	{
		if (*i_rg + find_next_char(rg, *i_rg, ']') == (int)ft_strlen(rg) - 1)
			*i_s = ft_strlen(s) - 1;
		k = *i_rg;
		while (rg[++k] && !is_char(rg, k, ']'))
		{
			j = *i_s - 1;
			while (s[++j])
			{
				if (s[j] == rg[k])
					break ;
			}
			if (s[j] == rg[k])
				break ;
		}
		if (s[j] != rg[k])
			return (free_rg_and_return(rg, FALSE));
		*i_rg += find_next_char(rg, *i_rg, ']') + 1;
		*i_s = j + 1;
	}
	return (TRUE);
}

int			can_skip_char(char *s, int i)
{
	int		q_mode;

	PUT2("1. s + i : ");PUT2(s + i);X('\n');
	q_mode = which_quotes(s, i);
	PUT2("q_mode : ");E(q_mode);X('\n');
	if (is_any_quote(s, i))
		return (TRUE);
	if (q_mode == NO_QUOTE && s[i] == '\\' && s[i + 1] != '\\')
		return (TRUE);
	if (q_mode == D_QUOTE && s[i] == '\\' &&
	(s[i + 1] == '$' || s[i + 1] ==  '\\' ||
	s[i + 1] ==  '`' || s[i + 1] ==  '"'))
		return (TRUE);
	return (FALSE);
}

int			is_next_all_char(char *s, char **rg, int *i_s, int *i_rg)
{
	if (which_quotes(*rg, *i_rg) == NO_QUOTE && is_char(*rg, *i_rg, '*'))
	{
		while ((*rg)[*i_rg] && is_char((*rg), *i_rg, '*'))
			*i_rg += 1;
		while ((*rg)[*i_rg] && can_skip_char(*rg, *i_rg))
			*i_rg += 1;
		if (!(*rg)[*i_rg])
		{
			*i_s = ft_strlen(s);
			return (free_rg_and_return((*rg), TRUE));
		}
		if (find_next_char((*rg), *i_rg, '*') < 0)
			*i_s = ft_strlen(s) - find_last_len((*rg) + *i_rg);
		if (!is_regex((*rg), *i_rg))
		{
			while (s[*i_s] && s[*i_s] != (*rg)[*i_rg])
				*i_s += 1;
			if (!s[*i_s])
			{
				return (free_rg_and_return((*rg), FALSE));
			}
		}
		else if (is_next_pool_char(s, *rg, i_s, i_rg) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int			match_regex(char *s, char *rg_ref)
{
	int		i_s;
	int		i_rg;
	char	*rg;

	if (!(rg = ft_strdup(rg_ref)))
		return (FALSE);
	if (rg_ref[ft_strlen(rg_ref) - 1] == '/')
		rg[ft_strlen(rg) - 1] = '#';
	i_s = 0;
	i_rg = 0;
//	PUT2("s : ");PUT2(s);X('\n');
	while (i_s < (int)ft_strlen(s) && i_rg < (int)ft_strlen(rg))
	{
		while (can_skip_char(rg, i_rg))
			i_rg++;
//		PUT2("2. rg +  i_rg : ");PUT2(rg + i_rg);X('\n');
		if (is_same_char(s, rg, &i_s, &i_rg) == FALSE)
			return (FALSE);
		while (can_skip_char(rg, i_rg))
			i_rg++;
		if (is_pool_char(s, rg, &i_s, &i_rg) == FALSE)
			return (FALSE);
		while (can_skip_char(rg, i_rg))
			i_rg++;
		if (is_next_all_char(s, &rg, &i_s, &i_rg) == FALSE)
			return (FALSE);
	}
	while (rg[i_rg] && rg[i_rg] == '*')
		i_rg += 1;
	if (i_s < (int)ft_strlen(s) || i_rg < (int)ft_strlen(rg))
		return (free_rg_and_return(rg, FALSE));
	return (free_rg_and_return(rg, TRUE));
}

int			insert_in_next(t_reg_path *c, t_reg_path **next, char *d_name)
{
	char			*t;
	char			*np;
	char			*no;

	t = ft_strcmp(c->path, "/") ? ft_strjoin(c->path, "/") : ft_strdup(c->path);
	np = ft_strjoin(t, d_name);
	ft_strdel(&t);
	if (c->is_abs == FALSE)
	{
		t = (c->out) ? ft_strjoin(c->out, "/") : NULL;
		no = ft_strjoin(t, d_name);
		ft_strdel(&t);
	}
	else
		no = NULL;
	if (*next == NULL)
		*next = ft_reg_pathnew(np, no, c->level + 1, c->is_abs);
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
				{
					insert_in_next(curr, next_path, dp->d_name);
				}
			}
		}
		closedir(dirp);
	}
	else
		return (FALSE);
	return (TRUE);
}

void		dispach_paths(t_reg_path *tmp, t_reg_path **nx, t_reg_path **f, int lvl)
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

t_reg_path	*replace_regex(char *s)
{
	char		**args;
	t_reg_path	*curr_paths;
	t_reg_path	*next_paths;
	t_reg_path	*final;
	t_reg_path	*tmp;
	int			i;

	if (is_regex_in_text(s) == FALSE)
		return (NULL);
	if (!(args = split_args(s)))
		return (NULL);
	next_paths = NULL;
	final = NULL;
	curr_paths = init_curr_path(s);
	i = -1;
	while (++i < (int)ft_tablen(args))
	{
		while (curr_paths)
		{
			keep_path(curr_paths, args[i], &next_paths);
			ft_strdel(&(curr_paths->path));
			ft_strdel(&(curr_paths->out));
			free(curr_paths);
			curr_paths = curr_paths->next;
		}
		tmp = next_paths;
		next_paths = NULL;
		dispach_paths(tmp, &next_paths, &final, ft_tablen(args));
		curr_paths = next_paths;
		next_paths = NULL;
	}
	if (next_paths)
		ft_reg_pathdestroy(&next_paths);
	if (curr_paths)
		ft_reg_pathdestroy(&curr_paths);
	ft_tabdel(args);
	return (final);
}
