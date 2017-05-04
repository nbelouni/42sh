/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:04:45 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:22:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		count_prev_char_in_quote(char *s, int *arr, int i, int quote)
{
	int len;

	len = 0;
	while (i - len >= 0 && s[i - len] == '\\' && arr[i - len] == quote)
	{
		len += 1;
	}
	return (len);
}

int		which_quotes(char *s, int len)
{
	int		w_quotes;
	int		i;

	w_quotes = 0;
	i = -1;
	while (++i < len)
	{
		if (is_char(s, i, '"'))
			w_quotes = (w_quotes == NO_QUOTE) ? D_QUOTE : NO_QUOTE;
		if (is_char(s, i, '\''))
			w_quotes = (w_quotes == NO_QUOTE) ? S_QUOTE : NO_QUOTE;
	}
	return (w_quotes);
}

int		supp_char(char *s, int i)
{
	int	j;

	j = i;
	while (j < (int)ft_strlen(s))
	{
		s[j] = s[j + 1];
		j++;
	}
	return (TRUE);
}

void	init_is_in_quote(char *s, int *is_in_quote)
{
	int		iiq_len;
	int		i;
	int		quote;
	int		supp;

	iiq_len = ft_strlen(s);
	i = 0;
	quote = NO_QUOTE;
	while (i < iiq_len)
	{
		supp = FALSE;
		if ((quote != D_QUOTE && is_char(s, i, '\'')) ||
		(quote != S_QUOTE && is_char(s, i, '"')))
		{
			if (quote != D_QUOTE && is_char(s, i, '\''))
				quote = (quote == NO_QUOTE) ? S_QUOTE : NO_QUOTE;
			if (quote != S_QUOTE && is_char(s, i, '"'))
				quote = (quote == NO_QUOTE) ? D_QUOTE : NO_QUOTE;
			supp = supp_char(s, i);
			iiq_len -= 1;
		}
		is_in_quote[i] = quote;
		if (supp == FALSE)
			i += 1;
	}
}

void	supp_quotes(char *s)
{
	int		is_in_quote[ft_strlen(s)];
	int		i;
	int		n_bs;
	int		j;
	int		keep_n_bs;

	init_is_in_quote(s, is_in_quote);
	i = ft_strlen(s);
	j = i;
	while (--i >= 0)
	{
		if ((is_in_quote[--j] == NO_QUOTE && s[i] == '\\') ||
		(is_in_quote[j] == D_QUOTE && (s[i + 1] &&
		(s[i + 1] == '$' || s[i + 1] == '\\' ||
		s[i + 1] == '"') && s[i] == '\\')))
		{
			n_bs = count_prev_char_in_quote(s, is_in_quote, i, is_in_quote[j]);
			keep_n_bs = n_bs / 2;
			n_bs = n_bs / 2 + n_bs % 2;
			while (n_bs > 0 && supp_char(s, i) && (i -= 1) >= 0)
				n_bs -= 1;
			i -= keep_n_bs;
		}
	}
}
