/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_buf_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:50:00 by alallema          #+#    #+#             */
/*   Updated: 2017/02/16 21:20:07 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int	i;
static int	len;
static int	type;
static int	level[2];
// bt = [0];
// bc = [1];

void	cut_space(char *s);
void	cut_cmd(t_token **list, char *s);

static int		(*tab_tok[8])() = {
	[0] = is_space,
	[1] = is_brace,
	[2] = is_bracket,
	[3] = is_dot,
	[4] = is_or_and,
	[5] = is_quot,
	[6] = is_agreg,
	[7] = is_redir,
};

void	reset_int(void)
{
	i = 0;
	len = 0;
	type = 0;
}

void	parse_list(t_token **list, char *s, int type)
{
	t_token	*new;

	new = ft_tokenew(type, s, level);
	if (!(*list))
		*list = new;
	else
		ft_tokenpush(list, new);
}

int		check_tok(char *s, int l)
{
	int		j;
	int		ret;

	j = 0;
	ret = 0;
	while (j < 8)
	{
		if ((ret = tab_tok[j](s, l)) != NO_TOKEN)
			return (ret);
		j++;
	}
	return (NO_TOKEN);
}

void	cut_space(char *s)
{
	while (is_space(s, i) == ESPACE)
		i++;
}

void	cut_cmd(t_token **list, char *s)
{
	cut_space(s);
	while (s[i + len] && check_tok(s, i + len) == NO_TOKEN)
		len++;
	type = CMD;
	if (len != 0)
		parse_list(list, ft_strsub(s, i, len), type);
	i = i + len;
	len = 0;
}

void	choose_pars(t_token **list, char *s, int ret)
{
	if (ret == ESPACE)
		cut_space(s);
	else
	{
		type = ret;
		if (ret > ESPACE && ret < OR)
		{
			if (ret == O_BRACKET)
				level[1]++;
			else if (ret == C_BRACKET)
				level[1]--;
			parse_list(list, ft_strsub(s, i, 1), ret);
		}
		if (ret > AMP  && ret <= C_BRACE)
		{
			parse_list(list, ft_strsub(s, i, 2), ret);
			if (ret == O_BRACE)
				level[0]++;
			if (ret == C_BRACE)
				level[0]--;
			i++;
		}
		i++;
	}
	cut_space(s);
}

int		parse_buf(t_token **lst, char *s)
{
	int		j;
	int		ret;

	reset_int();
	ret = 0;
	while (s[i])
	{
		j = -1;
		cut_cmd(lst, s);
		if ((ret = check_tok(s, i + len)) != NO_TOKEN)
			choose_pars(lst, s, ret);
	}
	PUT2("\n____________\n");
	return (1);
}
