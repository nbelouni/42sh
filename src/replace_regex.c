/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_regex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 13:41:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:10:19 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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
	begin = (s[0] == '/') ? 1 : 0;
	i = -1;
	while (++i < len)
	{
		end = 0;
		is_end(s, &end, '\'');
		is_end(s, &end, '`');
		is_end(s, &end, '"');
		end = (find_next_char(s, begin, '/') >= 0) ?
		end + find_next_char(s, begin, '/') : ft_strlen(s) - begin;
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

t_reg_path	*replace_regex(char *s)
{
	char		**args;
	t_reg_path	*curr_paths;
	t_reg_path	*final;
	int			i;

	if (is_regex_in_text(s) == FALSE)
		return (NULL);
	if (!(args = split_args(s)))
		return (NULL);
	final = NULL;
	curr_paths = init_curr_path(s);
	i = -1;
	while (++i < (int)ft_tablen(args))
	{
		find_regex(&curr_paths, &final, args[i], ft_tablen(args));
	}
	if (curr_paths)
		ft_reg_pathdestroy(&curr_paths);
	ft_tabdel(args);
	return (final);
}
