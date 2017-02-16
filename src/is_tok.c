/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:02:54 by alallema          #+#    #+#             */
/*   Updated: 2017/02/16 21:21:33 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		is_brace(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '{' && s[i + 1] && s[i + 1] == ' ')
			return (O_BRACE);
//		if (s[i] == '}')
//			return (C_BRACE);
	}
	return (0);
}

int		is_bracket(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '(')
			return (O_BRACKET);
		if (s[i] == ')')
			return (C_BRACKET);
	}
	return (0);
}

int		is_space(char *s, int i)
{
	if (s[i] == ' ')
		return (ESPACE);
	return (0);
}

int		is_dot(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == ';' && s[i + 1] == '}')
			return (C_BRACE);
		if (s[i] == ';')
			return (DOT);
	}
	return (0);
}

int		find_bracket_end(char *s, int i)
{
	int		len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if (i > 0 && s[i + len] && s[i + len] == ' ' && is_dot(s, i + len) == 1)
				break ;
			len++;
		}
		if (!s[i + len])
			return (-1);
		return (len);
	}
	return (0);
}

int		is_redir(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (!ft_strncmp(s + i, "<<", 2))
			return (DL_DIR);
		if (!ft_strncmp(s + i, ">>", 2))
			return (DR_DIR);
		if (s[i] == '>')
			return (SR_DIR);
		if (s[i] == '<')
			return (SL_DIR);
	}
	return (0);
}

int		is_agreg(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (!ft_strncmp(s + i, ">&", 2) || !ft_strncmp(s + i, "<&", 2))
			return (DIR_AMP);
		if (s[i] == '&')
			return (AMP);
	}
	return (0);
}

int		is_or_and(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '&' || s[i] == '|')
		{
			if (!ft_strncmp(s + i, "&&", 2))
				return (AND);
			if (!ft_strncmp(s + i, "||", 2))
				return (OR);
			if (s[i] == '|')
				return (PIPE);
		}
	}
	return (0);
}

int		is_quot(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '\'' || s[i] == '"' || s[i] == '`')
		{
			if (s[i] =='\'')
				return (S_QUOTE);
			if (s[i] =='"')
				return (D_QUOTE);
			if (s[i] =='`')
				return (BT_QUOTE);
		}
	}
	return (0);
}

/*
int		is_group(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '{' || s[i] == '(' || s[i] == ')' || s[i] == '}')
			return (1);
	}
	return (0);
}

int		is_separator(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '|' || s[i] == ';')
			return (1);
		if (!ft_strncmp(s + i, "||", 2) || !ft_strncmp(s + i, "&&", 2))
			return (2);
	}
	return (0);
}

int		is_redirection(char *s, int i)
{
	if (i > 0 || s[i - 1] != '\\')
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '&')
			return (1);
		if (!ft_strncmp(s + i, "<<", 2) || !ft_strncmp(s + i, ">>", 2)
		|| !ft_strncmp(s + i, "&>", 2))
			return (2);
	}
	return (0);
}

int		find_btquote_end(char *s, int i)
{
	int		len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if ((i + len == 0 || s[i + len - 1] != '\\') && s[i + len] == '`')
				break ;
			len++;
		}
		if (!s[i + len])
			return (-1);
		return (len);
	}
	return (0);
}
*/
