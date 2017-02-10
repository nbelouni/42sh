/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_ended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 16:50:08 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/10 16:01:35 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
 *	. . s . . l . . . 
 *	. . . . . . t . .
 *	. . t . . x x x x
 *
 *
 */
void		del_str(char *s, int start, int len)
{
	int		s_len;
	char	tmp[BUFF_SIZE];

	s_len = ft_strlen(s);
	if (s_len < start + len)
		return ;
	ft_bzero(tmp, sizeof(char) * BUFF_SIZE);
	ft_strncpy(tmp, s + start + len, s_len - len - start);
	ft_strncpy(s + start, tmp, s_len - len);
	ft_bzero(s + start + len, sizeof(char) * len);
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
	if (x == '"' && tmp[i - 1] == '\\' &&
	(tmp[i] == '$' || tmp[i] == '\\' || tmp[i] == '`' || tmp[i] == '"'))
		return (TRUE);
	return (FALSE);
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

int			can_close(int x, char *tmp, int i)
{
	if (i == 0 || (i > 0 && tmp[i - 1] != '\\'))
	{
		if (x == '`' && tmp[i] == '`')
			x = 0;
		else if (x == '"' && tmp[i] == '"')
			x = 0;
		else if (x == '(' && tmp[i] == ')')
			x = 0;
		else if (x == '[' && tmp[i] == ']')
			x = 0;
	}
	return (x);
}

t_bool		is_token(char *tmp, int i)
{
	while (tmp[i] && tmp[i] == ' ')
		i--;
	if (tmp[i] == '|' || tmp[i] == '&' || tmp[i] == ';')
		return (TRUE);
	return (FALSE);
}

int			can_end(char *tmp)
{
	int		btq;
	int		x;
	int		i;

	btq = 0;
	x = 0;
	i = -1;
	while (tmp[++i])
	{
		if (x == 0)
		{
//			if ((i == 0 || (i > 0 && tmp[i - 1] != '\\')) &&
//			tmp[i] = '\\')
//				supp_s(tmp, i, 1);
			if ((i == 0 || (i > 0 && tmp[i - 1] != '\\')) &&
			(tmp[i] == '\'' || tmp[i] == '"'
			|| tmp[i] == '(' || tmp[i] == '['))
				x = tmp[i];
			else if ((i == 0 || (i > 0 && tmp[i - 1] != '\\')) &&
			(tmp[i] == '`' ||
			 (tmp[i - 1] == '$' && tmp[i] == '(')))
				btq = '`';
			while (tmp[i] && btq == '`')
			{
				if ((i == 0 || (i > 0 && tmp[i - 1] != '\\')) &&
				(tmp[i] == '`' || tmp[i] == ')'))
					btq = 0;
				if (is_in_dquotes(tmp, x, i))
					del_str(tmp, i, 1);
				else if (tmp[i] == '\\')
					del_str(tmp, i, 1);
			}
			if (tmp[i] == '\\')
				del_str(tmp, i, 1);
		}
		else if (x == '\'' && tmp[i] == '\'')
			x = 0;
		else
		{
			x = can_close(x, tmp, i);
			if (x != '\'' && tmp[i] == '\\')
				del_str(tmp, i, 1);
			if (i == 0 || (i > 0 && tmp[i - 1] != '\\'))
			{
				if (x == '`' && tmp[i] == '`')
					x = 0;
				else if (x == '"' && tmp[i] == '"')
					x = 0;
				else if (x == '(' && tmp[i] == ')')
					x = 0;
				else if (x == '[' && tmp[i] == ']')
					x = 0;
			}
			else if (x == '\'' && tmp[i] == '\'')
				x = 0;
			if (is_in_dquotes(tmp, x, i))
				del_str(tmp, i, 1);
		}
	}
	if ((x == '(' || x == '{') && (i != 1 && !is_token(tmp, i)))
		return (ft_print_error("42sh: ", "command not found : ", ERR_WARNING));
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
	x = can_end(tmp);
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
