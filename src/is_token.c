/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 18:15:50 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/16 21:18:17 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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

int		is_btquote(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '`')
			return (1);
	}
	return (0);
}

int		is_new_btquote(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (!ft_strncmp(s + i, "$(", 2))
			return (2);
	}
	return (0);
}

int		is_dquote(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '"')
			return (1);
	}
	return (0);
}

int		is_squote(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '\'')
			return (1);
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

int		find_new_btquote_end(char *s, int i)
{
	int		len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if ((i + len == 0 || s[i + len - 1] != '\\') && s[i + len] == ')')
				break ;
			len++;
		}
		if (!s[i + len])
			return (-1);
		return (len);
	}
	return (0);
}

int		find_dollar(char *s, int i)
{
	int		len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if ((i + len == 0 || s[i + len - 1] != '\\') && s[i + len] == '$')
				break ;
			len++;
		}
		if (!s[i + len])
			return (-1);
		return (len);
	}
	return (0);
}

int		find_dquote_end(char *s, int i)
{
	int	len;
	int	btq;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len] && s[i + len] != '"')
		{
			if ((btq = is_btquote(s, i + len)))
				return (-1);
			else
				len++;
		}
		if (!s[i + len])
			return (0);
		return (len);
	}
	return (0);
}

int		find_squote_end(char *s, int i)
{
	int	len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if ((i + len == 0 || s[i + len - 1] != '\\') && s[i + len] == '\'')
				break ;
			len++;
		}
		if (!s[i + len])
			return (0);
		return (len);
	}
	return (0);
}

int		find_next_separator(char *s, int i)
{
	int len;
	int	b;

	len = 0;
	while (s[i + len])
	{
		b = is_separator(s, i + len);
		if (is_group(s, i + len))
			return (0);
		if (b)
			return (len + b);
		len++;
	}
	return (len);
}

int		find_group_end(char *s, int i, int token)
{
	int	len;
	int	dot;

	dot = 0;
	len = 0;
	if (token == C_BRACKET || token == C_BRACE)
		return (-1);
	if (i > 0 || s[i - 1] != '\\')
	{
		if (token == O_BRACKET) // '('
		{
			while (s[i + len])
			{
				if ((i + len <= 0 || s[i + len - 1] != '\\') && s[i + len] == ')')
					break;
				len ++;
			}
			if (!s[i + len])
				return (-1);
			return (len);
		}
		else if (token == O_BRACE)
		{
			while (s[i + len])
			{
				if ((i + len <= 0 || s[i + len - 1] != '\\') && s[i + len] == '}')
					break;
				len ++;
			}
			dot = len;
			while (dot >= 0)
			{
				if ((i + dot <= 0 || s[i + dot - 1] != '\\') && s[i + dot] == ';')
					break;
				dot--;
			}
			if (dot < 0)
				return (-1);
			if (!s[i + len])
				return (-1);
			return (len);
		}
	}
	return (0);
}
