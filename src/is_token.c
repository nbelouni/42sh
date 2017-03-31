/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 18:15:50 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/20 17:12:11 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		is_backslash(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '\\')
			return (1);
	}
	return (0);
}

int		is_char(char *s, int i, char c)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

int		find_prev_char(char *s, int len, char c)
{
	int		i;

	i = 0;
	while (len - i > 0)
	{
		if (is_char(s, len - i, c))
			return (i);
		i++;
	}
	return (0);
}

int		find_next_char(char *s, int len, char c)
{
	int		i;

	i = 0;
	while (len + i < (int)ft_strlen(s))
	{
		if (is_char(s, len + i, c))
			return (i);
		i++;
	}
	return (-1);
}

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

int		find_next_inhibitor(char *s, int i, int *token)
{
	int	len;

	len = 0;
	while (s[i + len])
	{
		if (is_squote(s, i + len))
			*token = S_QUOTE;
		else if (is_dquote(s, i + len))
			*token = D_QUOTE;
		else if (is_btquote(s, i + len))
			*token = BT_QUOTE;
		else if (is_new_btquote(s, i + len))
			*token = OBT_QUOTE;
		if (*token)
			return (len);
		len++;
	}
	return (len);
}

int		find_next_btq(char *s, int i, int *token)
{
	int	len;

	len = 0;
	while (s[i + len])
	{
		if (is_new_btquote(s, i + len))
		{
			*token = OBT_QUOTE;
			return (len);
		}
		else if (is_btquote(s, i + len))
		{
			*token = BT_QUOTE;
			return (len);
		}
		len++;
	}
	return (len);
}

int		find_btquote_end(char *s, int i)
{
	int		len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if (is_btquote(s, i + len))
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
	int		level;

	len = 0;
	level = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if ((i + len == 0 || s[i + len - 1] != '$') && s[i + len] == '(')
				level += 1;
			if ((i + len == 0 || s[i + len - 1] != '\\') && s[i + len] == ')')
			{
				if (level > 0)
					level -= 1;
				else
					break ;
			}
			len++;
		}
		if (!s[i + len])
			return (-1);
		return (len);
	}
	return (0);
}

int		find_next_nbtq(char *s, int i)
{
	int		len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if (is_new_btquote(s, i + len))
				return (len);
			len++;
		}
	}
	return (len);
}

int		find_dquote_end(char *s, int i)
{
	int	len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if (is_dquote(s, i + len))
				break ;
			len++;
		}
		if (!s[i + len])
			return (-1);
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
