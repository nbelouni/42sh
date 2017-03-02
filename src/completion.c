/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:10:02 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/02 22:17:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		is_char(char *s, int i, char c)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

int		is_any_quote(char *s, int i)
{
	if (is_dquote(s, i) || is_squote(s, i) ||
	is_new_btquote(s, i) || is_btquote(s, i))
		return (1);
	return (0);
}

int		is_cmd(char *s, int i)
{
	if (i < 0)
		return (1);
	while (i >= 0 && (is_char(s, i, ' ') || is_any_quote(s, i)))
		i--;
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

void	print_sort_list(t_sort_list *lst, int n)
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
		ft_putstr_fd(tmp->s, 1);
		i = -1;
		while ((int)ft_strlen(tmp->s) + ++i < max_len)
			ft_putchar_fd(' ', 1);
		word_per_line--;
		if (word_per_line == 0)
		{
			ft_putchar_fd('\n', 1);
			word_per_line = g_curs.win_col / max_len;
		}
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

int		fill_file(char *s, t_sort_list **lst, int begin)
{
	char			*path;
	DIR				*dirp;
	struct dirent	*dp;
	int				n_lst;

	(void)s;
	(void)begin;
	*lst = NULL;
	path = NULL;
	n_lst = 0;
	if (!(path = getcwd(NULL, 1024)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if ((dirp = opendir(path)) == NULL)
		return (ft_print_error("42sh: ", "No directory.", ERR_NEW_CMD));
	while ((dp = readdir(dirp)) != NULL)
	{
		if (insert_in_list(lst, dp->d_name) == ERR_EXIT)
			return (ERR_EXIT);
		n_lst++;
	}
	closedir(dirp);
	ft_strdel(&path);
	return (n_lst);
}

int		replace_or_print(t_buf *buf, t_sort_list *ref, int begin)
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
		print_sort_list(lst, n_lst);
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
		return (replace_or_print(buf, cplt->variable, begin + 1));
	if (is_char(buf->line, begin, '~'))
		return (replace_or_print(buf, cplt->username, begin + 1));
	if (is_char(buf->line, begin, '@'))
		return (replace_or_print(buf, cplt->hostname, begin + 1));
	if (is_cmd(buf->line, begin - 1))
		return (replace_or_print(buf, cplt->command, begin));
	if (is_arg(buf->line, begin - 1))
	{
		if ((ret = fill_file(buf->line, &ref, begin)) < 0)
			return (ret);
		ret = replace_or_print(buf, ref, begin);
		if (ref)
			destroy_sort_list(&ref);
		return (ret);
	}
	return (0);
}
