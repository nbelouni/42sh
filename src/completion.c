/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:10:02 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:19:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_core	*g_core;

void	print_slist(t_slist *lst, int n, char c)
{
	t_slist		*tmp;
	int			word_per_line;
	int			max_len;
	int			i;

	close_termios();
	tmp = lst;
	max_len = max_len_sort_lst(lst, n) + 3;
	if (max_len > g_curs.win_col)
		max_len = g_curs.win_col;
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

int		fill_file(t_buf *buf, t_slist **lst, int *bg)
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
	return (0);
}

int		replace_or_print(t_buf *buf, t_slist *ref, int begin, char c)
{
	int			n_lst;
	int			len;
	char		*s;
	t_slist		*lst;

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
		print_slist(lst, n_lst, c);
	if (n_lst > 1)
		return (TAB);
	if (n_lst == 1)
		return (0);
	return (-1);
}

int		complete_line(t_buf *buf, t_completion *cplt, char x)
{
	t_slist		*ref;
	int			begin;
	int			ret;

	if (x != TAB || buf->size >= BUFF_SIZE)
		return (0);
	begin = find_word_begin(buf->line,
	(g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len());
	if (is_char(buf->line, begin, '$') &&
	(ret = replace_or_print(buf, cplt->variable, begin + 1, '$')) >= 0)
		return (ret);
	if (is_char(buf->line, begin, '~') &&
	(ret = replace_or_print(buf, cplt->username, begin + 1, '~')) >= 0)
		return (ret);
	if (is_char(buf->line, begin, '~') && ret == -1)
		home_tild(buf, &begin);
	if (is_char(buf->line, begin, '@') &&
	(ret = replace_or_print(buf, cplt->hostname, begin + 1, '@')) >= 0)
		return (ret);
	if (is_cmd(buf->line, begin - 1) &&
	(ret = replace_or_print(buf, cplt->command, begin, 0)) >= 0)
		return (ret);
	ret = fill_file(buf, &ref, &begin) + replace_or_print(buf, ref, begin, 0);
	destroy_sort_list((ref) ? &ref : NULL);
	return (ret >= 0 ? ret : 0);
}
