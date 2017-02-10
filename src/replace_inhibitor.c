/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_ended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 16:50:08 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/07 23:06:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		del_str(char *s, int start, int len)
{
	int		s_len;
	char	tmp[BUFF_SIZE];

	PUT1("\ndel_str() : ");
	s_len = ft_strlen(s);
	if (s_len < start + len + 1)
		return ;
	ft_bzero(tmp, sizeof(char) * BUFF_SIZE);
	ft_strncpy(tmp, s + start + len, s_len - len - start);
	PUT1("\ntmp : ");
	PUT1(tmp);
	ft_strncpy(s + start, tmp, s_len - len);
	PUT1("\ns + start : ");
	PUT1(s + start);
	ft_bzero(s + start + ft_strlen(tmp), sizeof(char) * len);
	PUT1("\ns : ");
	PUT1(s);
}

void		add_str(char *s, char *new, int start, int len)
{
	int		s_len;
	int		tmp_len;
	char	tmp[BUFF_SIZE];

	s_len = ft_strlen(s);
	if (s_len <= 0)
		tmp_len = 0;
	else
		tmp_len = s_len - len - start + 1;
	ft_bzero(tmp, sizeof(char) * BUFF_SIZE);
	ft_strncpy(tmp, s + start + len, tmp_len);
	ft_strncpy(s + start, new, len);
	ft_strncpy(s + start + len, tmp, tmp_len);
}

t_bool		is_token(char *tmp, int i)
{
	while (tmp[i] && tmp[i] == ' ')
		i--;
	if (tmp[i] == '|' || tmp[i] == '&' || tmp[i] == ';')
		return (TRUE);
	return (FALSE);
}

t_bool		is_in_dquotes(char *tmp, int x, int i)
{
	if (x == '"' && i > 0 && tmp[i - 1] == '\\' &&
	(tmp[i] == '$' || tmp[i] == '\\' || tmp[i] == '`' || tmp[i] == '"'))
		return (TRUE);
	return (FALSE);
}

t_bool		is_old_btq(char *tmp, int i)
{
	if ((i > 0 || tmp[i - 1] != '\\')
	&& (tmp[i] == '$' || tmp[i + 1] == '('))
		return (FALSE);
	return (TRUE);
}

t_bool		is_in_aquotes(char *tmp, int x, int *i)
{
	if (is_in_dquotes(tmp, x, *i))
	{
		del_str(tmp, *i, 1);
		(*i)++;
		return (TRUE);
	}
	if ((x != '"' && x != '\'') && tmp[*i] == '\\')
	{
		del_str(tmp, *i, 1);
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

t_bool		is_comment(char *tmp, int x, int i)
{
	int		len;

	len = 0;
	if (tmp[i] != '#')
		return (FALSE);
	if (x == 0)
	{
		del_str(tmp, i, ft_strlen(tmp) - i);
		return (TRUE);
	}
	else if (x == '{')
	{
		while (tmp[i + len] && tmp[i + len] !='}')
			len++;
		if (tmp[i + len])
			del_str(tmp, i, len);
		return (TRUE);
	}
	else if (x == '(')
	{
		while (tmp[i + len] && tmp[i + len] !=')')
			len++;
		if (tmp[i + len])
			del_str(tmp, i, len);
		return (TRUE);
	}
	else if (x == '`')
	{
		while (tmp[i + len] && tmp[i + len] !='`')
			len++;
		if (tmp[i + len])
			del_str(tmp, i, len);
		return (TRUE);
	}
	return (FALSE);
}

int			is_limit(char c)
{
	if (c == '\'' || c == '"' || c == '`' || c == '[' || c == '(' || c == '{')
		return (c);
	return (0);
}
char		modify_buf(char *tmp)
{
	int		i;
	int		x;

	i = -1;
	x = 0;
	while (tmp[++i])
	{
		X(tmp[i]);
		if (x == 0)
			x = is_limit(tmp[i]);
//		if (is_old_btq(tmp, i) == FALSE)
//			return (-1);
		if (!is_in_aquotes(tmp, x, &i))
			is_comment(tmp, x, i);
//		if (x != 0 && is_limit(tmp[i]))
//			x = 0;
	}
	PUT1("\nx : ");
	E(x);X('\n');
	return (x);
}

int			is_line_ended(t_buf *buf)
{
	int		x;
	char	tmp[BUFF_SIZE];

	ft_bzero(tmp, sizeof(char) * BUFF_SIZE);
	if (buf->final_line)
		add_str(tmp, buf->final_line, 0, ft_strlen(buf->final_line));
	add_str(tmp, buf->line, ft_strlen(buf->final_line), buf->size);
	if ((x = modify_buf(tmp)) < 0)
		return (ft_print_error("42sh: ", ERR_EXPR_SYNT, ERR_NEW_CMD));
	free(buf->final_line);
	buf->final_line = 0;
	if (!(buf->final_line = ft_strdup(tmp)))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	if (x)
	{
		set_prompt(PROMPT2, ft_strlen(PROMPT2));
		return (ERR_NEW_CMD);
	}
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	return (TRUE);
}
