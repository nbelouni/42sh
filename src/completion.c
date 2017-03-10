/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:10:02 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/07 20:09:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		is_any_quote(char *s, int i)
{
	if (is_dquote(s, i) || is_squote(s, i) ||
	is_new_btquote(s, i) || is_btquote(s, i))
		return (1);
	return (0);
}

int		is_cmd(char *s, int i)
{
	while (i >= 0 && (is_char(s, i, ' ') || is_any_quote(s, i)))
		i--;
	if (i < 0)
		return (1);
	if (i >= 0 &&
	(is_separator(s, i) || is_char(s, i, '(') || is_char(s, i, '{')))
		return (1);
	return (0);
}

int		is_arg(char *s, int i)
{
	if (i < 0)
		return (1);
	while (i >= 0 && is_char(s, i, ' '))
		i--;
	if (i >= 0 && !is_separator(s, i) && !is_group(s, i))
		return (1);
	return (0);
}

int		find_word_begin(char *s)
{
	int i;

	i = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len();
	while (i >= 0)
	{
		if (is_char(s, i, '(') || is_separator(s, i) ||
		is_redirection(s, i) || is_space(s, i) ||
		is_any_quote(s, i))
			return (i + 1);
		else if (i == 0)
			return (i);
		i--;
	}
	return (0);
}

int		find_word_end(char *s)
{
	int i;

	i = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len();
	while (s[i])
	{
		if (is_brace(s, i) == O_BRACE || is_separator(s, i) ||
		is_redirection(s, i) || is_space(s, i) || is_any_quote(s, i))
			return (i);
		i++;
	}
	return (i);
}

int		find_cplt(char *s, t_sort_list *ref, t_sort_list **lst, int len)
{
	t_sort_list	*tmp;
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

int		count_sort_lst(t_sort_list *lst)
{
	t_sort_list	*tmp;
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

int		max_len_sort_lst(t_sort_list *lst, int n)
{
	t_sort_list	*tmp;
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

void	print_sort_list(t_sort_list *lst, int n, char c)
{
	t_sort_list	*tmp;
	int			word_per_line;
	int			max_len;
	int			i;

	close_termios();
	tmp = lst;
	max_len = max_len_sort_lst(lst, n) + 3;
	word_per_line = g_curs.win_col / max_len;
	ft_putchar_fd('\n', 1);
	while (n-- && tmp)
	{
		write(1, &c, 1);
		ft_putstr_fd(tmp->s, 1);
		i = -1;
		while ((int)ft_strlen(tmp->s) + ++i < max_len)
			ft_putchar_fd(' ', 1);
		word_per_line--;
		if (word_per_line == 0)
			word_per_line = g_curs.win_col / max_len + ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	ft_putchar_fd('\n', 1);
}

int		replace_cplt(t_buf *buf, char *ref, int bg)
{
	int		len;
	int		i;

	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - bg;
	while (len-- > 0)
		vb_del(buf, DEL);
	len = ft_strlen(ref);
	i = -1;
	while (++i < len)
		vb_insert(buf, &(ref[i]));
	buf->size = ft_strlen(buf->line);
	return (0);
}

int		open_abs_path(char *s, DIR **dirp, int *bg)
{
	char			*extend_path;
	char			*final_path;
	int				len;

	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - *bg;
	if (!(extend_path = ft_strsub(s, *bg, len)))
		return (ft_print_error("42sh: ", ERR_MALLOC, 0));
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
			return (ft_print_error("42sh: ", "No directory.", 0));
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
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(extend_path = ft_strsub(s, *bg, len)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	final_len = ft_strlen(curr_path) + ft_strlen(extend_path) + 2;
	if (!(final_path = ft_strnew(final_len)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	ft_multi_concat(final_path, curr_path, "/", extend_path);
	if (!(*dirp = can_open_path(final_path, curr_path, extend_path, bg)))
		return (0);
	ft_strdel(&curr_path);
	ft_strdel(&extend_path);
	ft_strdel(&final_path);
	return (TRUE);
}

int		fill_file(t_buf *buf, t_sort_list **lst, int *bg)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				n_lst;
	int				len;

	*lst = NULL;
	n_lst = 0;
	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - *bg;
	if (buf->line[*bg] == '/')
	{
		if (open_abs_path(buf->line, &dirp, bg) != TRUE)
			return (ERR_EXIT);
	}
	else if (open_rel_path(buf->line, &dirp, bg) != TRUE)
		return (ERR_EXIT);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (insert_in_list(lst, dp->d_name) == ERR_EXIT)
			return (ERR_EXIT);
		n_lst++;
	}
	closedir(dirp);
	return (n_lst);
}

int		replace_or_print(t_buf *buf, t_sort_list *ref, int begin, char c)
{
	int			n_lst;
	int			len;
	char		*s;
	t_sort_list	*lst;

	s = buf->line;
	lst = NULL;
	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - begin;
	if (!s[0])
	{
		lst = ref;
		n_lst = count_sort_lst(ref);
	}
	else
		n_lst = find_cplt(s + begin, ref, &lst, len);
	if (n_lst == 1)
		replace_cplt(buf, lst->s, begin);
	else if (n_lst > 1)
		print_sort_list(lst, n_lst, c);
	return (n_lst > 1 ? TAB : 0);
}

int		complete_line(t_buf *buf, t_completion *cplt, char x)
{
	t_sort_list	*ref;
	int			begin;
	int			ret;

	if (x != TAB)
		return (0);
	begin = find_word_begin(buf->line);
	if (is_char(buf->line, begin, '$'))
		return (replace_or_print(buf, cplt->variable, begin + 1, '$'));
	if (is_char(buf->line, begin, '~'))
		return (replace_or_print(buf, cplt->username, begin + 1, '~'));
	if (is_char(buf->line, begin, '@'))
		return (replace_or_print(buf, cplt->hostname, begin + 1, '@'));
	if (is_cmd(buf->line, begin - 1))
		return (replace_or_print(buf, cplt->command, begin, 0));
	if (is_arg(buf->line, begin - 1))
	{
		if ((ret = fill_file(buf, &ref, &begin)) < 0)
			return (ret);
		ret = replace_or_print(buf, ref, begin, 0);
		if (ref)
			destroy_sort_list(&ref);
		return (ret);
	}
	return (0);
}
