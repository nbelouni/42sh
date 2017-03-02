/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:10:02 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/02 17:06:30 by nbelouni         ###   ########.fr       */
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
	if (is_dquote(s, i) || is_squote(s, i) || is_new_btquote(s, i))
		return (1);
	return (0);
}

int		find_word_begin(char *s)
{
	int i;

	i = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len();
	while (i >= 0)
	{
		if (is_char(s, i, '(') || is_separator(s, i) || is_redirection(s, i) || is_space(s, i) ||
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
		if (is_brace(s, i) == O_BRACE || is_separator(s, i) || is_redirection(s, i) || is_space(s, i) || is_any_quote(s, i))
			return (i);
		i++;
	}
	return (i);
}

int		find_cplt(char *s, t_sort_list *ref, t_sort_list **lst, int len)
{
	t_sort_list	*tmp;
	int			n_lst;

	PUT2("_________1\n");
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

void	print_sort_list(t_sort_list *lst, int n)
{
	t_sort_list	*tmp;

	tmp = lst;
	while (n && tmp)
	{
		PUT2(tmp->s);X(' ');
		n--;
		tmp = tmp->next;
	}
	X(' ');
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

int		replace_cplt(t_buf *buf, char *ref, int begin)
{
	int		len;
	int		i;

	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - begin;
	while (len-- > 0)
		vb_del(buf, DEL);
	len = ft_strlen(ref);
	i = -1;
	while (++i < len)
		vb_insert(buf, &(ref[i]));
	vb_insert(buf, " ");
	buf->size = ft_strlen(buf->line);
	return (0);
}

int		replace_or_print(t_buf *buf, t_sort_list *ref, int begin)
{
	int		n_lst;
	int		len;
	char	*s;
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
		return (replace_cplt(buf, lst->s, begin));
	else
		print_sort_list(lst, n_lst);
	return (TAB);
}

int		complete_line(t_buf *buf, t_completion *cplt, char x)
{
	int		begin;
//	int		end;

	(void)cplt;
	if (x != TAB)
		return (0);
	begin = find_word_begin(buf->line);
//	end = find_word_end(buf->line);
	PUT2("buf->line + begin : -");
	PUT2(buf->line + begin);PUT2("-\n");
	if (is_char(buf->line, begin, '$'))
		return (replace_or_print(buf, cplt->variable, begin + 1));
	if (is_char(buf->line, begin, '~'))
		return (replace_or_print(buf, cplt->username, begin + 1));
	if (is_char(buf->line, begin, '@'))
		return (replace_or_print(buf, cplt->hostname, begin + 1));
	return (0);
}
