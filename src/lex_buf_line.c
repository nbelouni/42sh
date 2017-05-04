/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_buf_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:50:00 by alallema          #+#    #+#             */
/*   Updated: 2017/05/03 20:45:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int		(*g_tab_tok[9])() = {
	[0] = is_space,
	[1] = is_dot,
	[2] = is_or_and,
	[3] = is_agreg,
	[4] = is_redir,
	[5] = is_dquote,
	[6] = is_squote,
	[7] = find_dquote_end,
	[8] = find_squote_end,
};

int			check_tok(char *s, int l)
{
	int		j;
	int		ret;

	j = 0;
	ret = 0;
	while (j < 5)
	{
		if ((ret = g_tab_tok[j](s, l)) != 0)
			return (ret);
		j++;
	}
	return (NO_TOKEN);
}

int			cut_quote(char *s, t_pt *p)
{
	int		j;
	int		ret;

	j = 5;
	ret = 0;
	while (j < 7 && (ret = g_tab_tok[j](s, p->i + p->len)) == 0)
		j++;
	if (j == 7 && ret == 0)
		return (0);
	else
	{
		ret = g_tab_tok[j + 2](s, p->i + p->len + 1);
		if (ret == 0 && s[p->i + p->len] != s[p->i + p->len + 1])
			p->len = ft_strlen(s);
		else
			p->len = ret + p->len + 1;
		return (0);
	}
	return (0);
}

static int	choose_pars(t_token **list, char *s, int rt, t_pt *p)
{
	int		r;
	int		len;

	p->type = rt;
	if (rt > ESPACE && rt < FD_IN)
	{
		len = (rt >= OR && rt <= DIR_R_AMP) ? 2 : 1;
		if ((r = parse_list(list, ft_strsub(s, p->i, len), p)))
			return (r);
		if (rt >= OR && rt <= DIR_R_AMP)
			p->i++;
	}
	p->i++;
	if ((rt == DIR_L_AMP || rt == DIR_R_AMP) && (r = check_fd_out(list, s, p)))
		return (r);
	p->i = cut_space(s, p->i);
	return (0);
}

int			parse_buf(t_token **lst, char *s, t_completion *compl, t_lst *hist)
{
	int		j;
	int		ret;
	int		ret_lex;
	t_pt	p;

	reset_int_pt(&p);
	ret = 0;
	while (p.i < (int)ft_strlen(s))
	{
		j = -1;
		if ((ret_lex = cut_cmd(lst, s, &p)))
			return (return_new_prompt(ret_lex));
		if (p.i + p.len < (int)ft_strlen(s) &&
				(ret = check_tok(s, p.i + p.len)) != NO_TOKEN)
		{
			if (ret == ESPACE)
				p.i = cut_space(s, p.i);
			else if ((ret_lex = choose_pars(lst, s, ret, &p)))
				return (return_new_prompt(ret_lex));
		}
	}
	if (sort_list_token(lst, compl, hist) == ERR_NEW_CMD)
		return (ERR_NEW_CMD);
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	return (can_create_tree(*lst));
}
