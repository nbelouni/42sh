/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_ended.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 16:50:08 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/09 19:22:29 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			can_close(int x, char *tmp, int i)
{
	if (i == 0 || (i > 0 && tmp[i - 1] != '\\'))
	{
		if (x == '`' && tmp[i] == '`')
			x = 0;
		else if (x == '"' && tmp[i] == '"')
			x = 0;
		else if (x == '{' && tmp[i] == '}')
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
	int		x;
	int		i;

	x = 0;
	i = -1;
	while (tmp[++i])
	{
		if (x == 0)
		{
			if ((i == 0 || (i > 0 && tmp[i - 1] != '\\')) &&
			(tmp[i] == '`' || tmp[i] == '\'' || tmp[i] == '"'
			|| tmp[i] == '{' || tmp[i] == '(' || tmp[i] == '['))
				x = tmp[i];
		}
		else if (x == '\'' && tmp[i] == '\'')
			x = 0;
		else
			x = can_close(x, tmp, i);
	}
	if ((x == '(' || x == '{') && (i != 1 && !is_token(tmp, i)))
		return (ft_print_error("42sh: ", "command not found : ", ERR_WARNING));
	return (x);
}

int			is_line_ended(t_buf *buf)
{
	int		x;
	char	*tmp;

	if (!(tmp = ft_strjoin(buf->final_line, buf->line)))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	x = can_end(tmp);
	free(buf->final_line);
	buf->final_line = 0;
	buf->final_line = tmp;
	if (x)
	{
		set_prompt(PROMPT2, ft_strlen(PROMPT2));
		return (ERR_NEW_CMD);
	}
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	return (TRUE);
}
