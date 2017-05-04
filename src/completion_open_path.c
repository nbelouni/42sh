/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_open_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 22:36:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:19:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		open_abs_path(char *s, DIR **dirp, int *bg)
{
	char			*extend_path;
	char			*final_path;
	int				len;

	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - *bg;
	if (!(extend_path = ft_strsub(s, *bg, len)))
		return (ft_print_error("21sh: ", ERR_MALLOC, 0));
	final_path = extend_path;
	if ((*dirp = opendir(final_path)) == NULL)
	{
		while (len > 0 && final_path[len] != '/')
		{
			final_path[len] = 0;
			len--;
		}
		free(*dirp);
		if ((*dirp = opendir(final_path)) == NULL)
			return (ft_print_error("21sh: ", "No directory.", 0));
	}
	if (ft_strlen(final_path) > 0)
		*bg += ft_strlen(final_path);
	ft_strdel(&final_path);
	return (TRUE);
}

void	supp_last_path_part(char *s)
{
	int				len;

	len = ft_strlen(s);
	while (len > 0 && s[len] != '/')
	{
		s[len] = 0;
		len--;
	}
}

DIR		*can_open_path(char *fpath, char *cpath, char *extend_path, int *begin)
{
	DIR	*dirp;

	if ((dirp = opendir(fpath)) == NULL)
	{
		supp_last_path_part(fpath);
		if ((dirp = opendir(fpath)) == NULL)
		{
			if ((dirp = opendir(cpath)) == NULL)
				return (NULL);
		}
		else if (find_prev_char(extend_path, ft_strlen(extend_path) - 1, '/'))
		{
			supp_last_path_part(extend_path);
			if (ft_strlen(extend_path) > 0)
				*begin += ft_strlen(extend_path);
		}
	}
	else if (ft_strlen(extend_path) > 0)
		*begin += ft_strlen(extend_path);
	return (dirp);
}

int		open_rel_path(char *s, DIR **dirp, int *bg)
{
	char			*curr_path;
	char			*extend_path;
	char			*final_path;
	int				len;
	int				final_len;

	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - *bg;
	if (!(curr_path = getcwd(NULL, 1024)))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(extend_path = ft_strsub(s, *bg, len)))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	final_len = ft_strlen(curr_path) + ft_strlen(extend_path) + 2;
	if (!(final_path = ft_strnew(final_len)))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	ft_multi_concat(final_path, curr_path, "/", extend_path);
	if (!(*dirp = can_open_path(final_path, curr_path, extend_path, bg)))
		return (0);
	ft_strdel(&curr_path);
	ft_strdel(&extend_path);
	ft_strdel(&final_path);
	return (TRUE);
}
