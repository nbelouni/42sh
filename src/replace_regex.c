/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_regex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 16:24:49 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/23 02:03:10 by nbelouni         ###   ########.fr       */
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
	if (s[0] != '/')
		n_slash++;
	return (n_slash);
}

char	**split_args(char *s)
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
	i = 0;
	while (i < len)
	{
		end = find_next_char(s, begin, '/');
		if (end == -1)
			end = ft_strlen(s) - begin;
		if (!(new[i] = ft_strsub(s, begin, end + 1)))
			return (NULL);
		PUT2("new[i] : ");PUT2(new[i]);X('\n');
		begin += end + 1;
		i++;
	}
	new[len] = NULL;
	PUT2("len : ");E(len);X('\n');
	i = 0;
	while (new[i])
	{
		PUT2("new[i] : ");PUT2(new[i]);X('\n');
		i++;
	}
	return (new);
}

t_reg_path	*init_curr_path(char *s)
{
	char		*path;

	if (s[0] == '/')
	{
		if (!(path = ft_strdup("/")))
			return (NULL);
	}
	else
	{
		if (!(path = getcwd(NULL, 1024)))
			return (NULL);
	
	}
	return (ft_reg_pathnew(path, 0));
}

int		is_regex(char *s, int i)
{
	if (is_char(s, i, '?') || is_char(s, i, '[') || is_char(s, i, '*'))
		return (TRUE);
	return (FALSE);
}

int		find_last_len(char *s)
{
	int		i;
	int		len;
	i = -1;
	len = 0;
	PUT2("find_last_len()\n");
	PUT2("!find_next_char(*)\n");
		while (++i < (int)ft_strlen(s))
		{
			if (is_char(s, i, '['))
				i += find_next_char(s + i, 0, ']');
			len++;
		}
	PUT2("len : ");E(len);X('\n');
	return (len);
}

int		match_regex(char *s, char *rg_ref)
{
	int		i_s;
	int		i_rg;
	char	*rg;

	rg = ft_strdup(rg_ref);
	if (rg_ref[ft_strlen(rg_ref) - 1] == '/')
		rg[ft_strlen(rg) - 1] = 0;
//	PUT2("match_regex(");PUT2(s);PUT2(", ");PUT2(rg);PUT2(")\n");
	i_s = 0;
	i_rg = 0;
	while (i_s < (int)ft_strlen(s) && i_rg < (int)ft_strlen(rg))
	{
//		PUT2("rg + i_rg : ");PUT2(rg + i_rg);X('\n');
//		PUT2("s + i_s : ");PUT2(s + i_s);X('\n');
		if (is_regex(rg, i_rg) == FALSE)
		{
//			PUT2("!regex\n");
			if (rg[i_rg] != s[i_s])
				return (FALSE);
			rg += 1;
			i_s += 1;
		}
		else if (rg[i_rg] == '?')
		{
//			PUT2("regex == ?\n");
			if (rg[i_rg] != s[i_s])
			if (!s[i_s])
				return (FALSE);
			i_rg += 1;
			i_s += 1;
		}
		else if (rg[i_rg] == '[')
		{
//			PUT2("regex == [\n");
			i_rg += 1;
			while (rg[i_rg])
			{
				if (is_char(rg, i_rg, ']'))
					break ;
				else if (s[i_s] == rg[i_rg])
					break ;
				i_rg += 1;
			}
			if (is_char(rg, i_rg, ']'))
				return (FALSE);
			i_rg += find_next_char(rg, i_rg, ']') + 1;
			i_s++;
		}
		else if (rg[i_rg] == '*')
		{
//			PUT2("regex == *\n");
			while (rg[i_rg] && is_char(rg, i_rg, '*'))
				i_rg += 1;
			if (!rg[i_rg])
				return (TRUE);
//		PUT2("rg + i_rg : ");PUT2(rg + i_rg);X('\n');
//		PUT2("NEXT_CHAR : ");E(find_next_char(rg, i_rg, '*'));X('\n');
			if (find_next_char(rg, i_rg, '*') < 0)
				i_s = ft_strlen(s) - find_last_len(rg + i_rg);
//			PUT2("s + i_s : ");PUT2(s + i_s);X('\n');
			if (!is_regex(rg, i_rg))
			{
				while (s[i_s] && s[i_s] != rg[i_rg])
					i_s += 1;
			}
			else if (rg[i_rg] == '[')
			{
				int	j;
				int	k;

				k = i_rg + 1;
				if (i_rg + find_next_char(rg, i_rg, ']') == (int)ft_strlen(rg) - 1)
					i_s = ft_strlen(s) - 1;
				while (rg[k] && !is_char(rg, k, ']'))
				{
					j = i_s;
					while (s[j])
					{
						if (s[j] == rg[k])
						{
//				PUT2("rg + k : ");PUT2(rg + k);X('\n');
//				PUT2("s + j : ");PUT2(s + j);X('\n');
							break ;
						}
						j += 1;
					}
					if (s[j] == rg[k])
					{
//				PUT2("rg + k : ");PUT2(rg + k);X('\n');
//				PUT2("s + j : ");PUT2(s + j);X('\n');
						break ;
					}
					k += 1;
				}
//				PUT2("rg + k : ");PUT2(rg + k);X('\n');
//				PUT2("s + j : ");PUT2(s + j);X('\n');
				if (s[j] != rg[k])
					return (FALSE);
				i_rg += find_next_char(rg, i_rg, ']') + 1;
				i_s = j + 1;
			}
//			PUT2("rg + i_rg : ");PUT2(rg + i_rg);X('\n');
//			PUT2("s + i_s : ");PUT2(s + i_s);X('\n');
		}
	}
	if (rg[i_rg] == '*')
	{
		while (rg[i_rg] && rg[i_rg] == '*')
			i_rg += 1;
	}
	if (i_s < (int)ft_strlen(s) || i_rg < (int)ft_strlen(rg))
		return (FALSE);
	return (TRUE);
}

int		keep_path(t_reg_path *curr, char *rg, t_reg_path **next_path)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*tmp;

//	PUT2("rg : ");PUT2(rg);X('\n');
	if ((dirp = opendir(curr->path)) != NULL)
	{
		while ((dp = readdir(dirp)) != NULL)
		{
			if ((rg[0] != '.' && dp->d_name[0] != '.') ||
			(rg[0] == '.' && dp->d_name[0] == '.'))
			{
				if (!is_regex_in_text(rg))
				{
					if (!ft_strncmp(dp->d_name, rg, ft_strlen(rg) - 1))
					{
						if (ft_strcmp(curr->path, "/"))
							tmp = ft_strjoin(curr->path, "/");
						else
							tmp = ft_strdup(curr->path);
						if (*next_path == NULL)
							*next_path = ft_reg_pathnew(ft_strjoin(tmp, dp->d_name), curr->level  + 1);
						else
							ft_reg_pathadd(next_path, ft_reg_pathnew(ft_strjoin(tmp, dp->d_name), curr->level  + 1));
                
					}
				}
				else
				{
					if (match_regex(dp->d_name, rg) == TRUE)
					{
						if (ft_strcmp(curr->path, "/"))
							tmp = ft_strjoin(curr->path, "/");
						else
							tmp = ft_strdup(curr->path);
						if (*next_path == NULL)
							*next_path = ft_reg_pathnew(ft_strjoin(tmp, dp->d_name), curr->level  + 1);
						else
							ft_reg_pathadd(next_path, ft_reg_pathnew(ft_strjoin(tmp, dp->d_name), curr->level  + 1));
                
					}
				}
			}
		}
		closedir(dirp);
	}
	else
		return (FALSE);
	return (TRUE);
}

void	dispach_paths(t_reg_path *tmp, t_reg_path **next, t_reg_path **final, int max_lvl)
{
	while (tmp)
	{
		if ((tmp)->level == max_lvl)
		{
			if (*final)
				ft_reg_pathpush(final, tmp);
			else
				*final = tmp;
		}
		else
		{
			if (*next)
				ft_reg_pathpush(next, tmp);
			else
				*next = tmp;
		}
		tmp = (tmp)->next;
		if (tmp)
		{
			(tmp)->prev->next = NULL;
			(tmp)->prev = NULL;
		}
	}
}

/*
 *	bash-3.2$ echo *\/
 *	-> doc/ inc/ libft/ obj/ src/
 *
 */
t_token	*replace_regex(char *s)
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
	i = -1;
	while (args[++i])
	{
		PUT2("args[i] : ");PUT2(args[i]);X('\n');
	}
	next_paths = NULL;
	final = NULL;
	curr_paths = init_curr_path(s);
	i = -1;
	PUT2("_________________\n");
	PUT2("args len : ");E(ft_tablen(args));X('\n');
	while (++i < (int)ft_tablen(args))
	{
		PUT2("curr_paths->path : ");PUT2(curr_paths->path);X('\n');
		PUT2("curr_paths->level : ");E(curr_paths->level);X('\n');
		while (curr_paths)
		{
			if (keep_path(curr_paths, args[i], &next_paths) == TRUE)
			{
				tmp = next_paths;
				while (tmp)
				{
					PUT2("tmp->path : ");PUT2(tmp->path);X('\n');
					PUT2("tmp->level : ");E(tmp->level);X('\n');
					tmp = tmp->next;
				}
			}
			ft_strdel(&(curr_paths->path));
			free(curr_paths);
			curr_paths = curr_paths->next;
			PUT2("okok\n");
		}
		tmp = next_paths;
		next_paths = NULL;
		dispach_paths(tmp, &next_paths, &final, ft_tablen(args));
		t_reg_path *tmp2;
		tmp2 = tmp;
		PUT2("TMP :\n");
		while (tmp2)
		{
			PUT2("tmp->path : ");PUT2(tmp2->path);X('\n');
			PUT2("tmp->level : ");E(tmp2->level);X('\n');
			tmp2 = tmp2->next;
		}
		tmp2 = next_paths;
		PUT2("NEXT_PATHS :\n");
		while (tmp2)
		{
			PUT2("next_paths->path : ");PUT2(tmp2->path);X('\n');
			PUT2("next_paths->level : ");E(tmp2->level);X('\n');
			tmp2 = tmp2->next;
		}
		tmp2 = final;
		PUT2("FINAL :\n");
		while (tmp2)
		{
			PUT2("final->path : ");PUT2(tmp2->path);X('\n');
			PUT2("final->level : ");E(tmp2->level);X('\n');
			tmp2 = tmp2->next;
		}
		curr_paths = next_paths;
		next_paths = NULL;
	}
	tmp = final;
	PUT2("FINAL :\n");
	while (tmp)
	{
		PUT2("final->path : ");PUT2(tmp->path);X('\n');
		tmp = tmp->next;
	}
	return (NULL);
}
