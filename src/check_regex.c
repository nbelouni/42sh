/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_regex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 21:02:27 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:02:35 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			is_regex_in_text(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '?') || is_char(s, i, '*'))
			return (TRUE);
		else if (is_char(s, i, '['))
		{
			is_end(s, &i, '\'');
			is_end(s, &i, '`');
			is_end(s, &i, '"');
			if (find_next_char(s, i + 1, ']') >= 0)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int			is_regex(char *s, int i)
{
	if (which_quotes(s, i) == NO_QUOTE)
	{
		if (is_char(s, i, '?') || is_char(s, i, '*'))
			return (TRUE);
		if (is_char(s, i, '['))
		{
			while (i < (int)ft_strlen(s) && !is_char(s, i, ']'))
			{
				is_end(s, &i, '\'');
				is_end(s, &i, '`');
				is_end(s, &i, '"');
				i++;
			}
			if (i < (int)ft_strlen(s))
				return (TRUE);
		}
	}
	return (FALSE);
}

int			find_last_len(char *s)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (++i < (int)ft_strlen(s))
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '['))
		{
			while (++i < (int)ft_strlen(s))
			{
				is_end(s, &i, '\'');
				is_end(s, &i, '`');
				is_end(s, &i, '"');
				if (is_char(s, i, ']'))
					break ;
			}
		}
		len++;
	}
	return (len);
}

int			can_skip_char(char *s, int i)
{
	int		q_mode;

	q_mode = which_quotes(s, i);
	if (is_any_quote(s, i))
		return (TRUE);
	if (q_mode == NO_QUOTE && s[i] == '\\' && s[i + 1] != '\\')
		return (TRUE);
	if (q_mode == D_QUOTE && s[i] == '\\' &&
	(s[i + 1] == '$' || s[i + 1] == '\\' ||
	s[i + 1] == '`' || s[i + 1] == '"'))
		return (TRUE);
	return (FALSE);
}

int			count_slashs(char *s)
{
	int	i;
	int	n_slash;

	i = -1;
	n_slash = 0;
	while (s[++i])
	{
		is_end(s, &i, '\'');
		is_end(s, &i, '`');
		is_end(s, &i, '"');
		if (is_char(s, i, '/'))
			n_slash++;
	}
	if (s[0] != '/')
		n_slash++;
	return (n_slash);
}
