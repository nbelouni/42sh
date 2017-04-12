/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_buf_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:50:00 by alallema          #+#    #+#             */
/*   Updated: 2017/04/08 18:24:03 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int		(*g_tab_tok[15])() = {
	[0] = is_space,
	[1] = is_brace,
	[2] = is_bracket,
	[3] = is_dot,
	[4] = is_or_and,
	[5] = is_agreg,
	[6] = is_redir,
	[7] = is_btquote,
	[8] = is_new_btquote,
	[9] = is_dquote,
	[10] = is_squote,
	[11] = find_btquote_end,
	[12] = find_new_btquote_end,
	[13] = find_dquote_end,
	[14] = find_squote_end,
};

int			check_tok(char *s, int l)
{
	int		j;
	int		ret;

	j = 0;
	ret = 0;
	while (j < 7)
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

	j = 7;
	ret = 0;
	while (j < 11 && (ret = g_tab_tok[j](s, p->i + p->len)) == 0)
		j++;
	if (j == 11 && ret == 0)
		return (0);
	else
	{
		ret = g_tab_tok[j + 4](s, p->i + p->len + 1);
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
		len = (rt >= OR && rt <= O_BRACE) ? 2 : 1;
		if (rt == C_BRACKET)
			p->level[0]--;
		if (rt == C_BRACE)
			p->level[1]--;
		if ((r = parse_list(list, ft_strsub(s, p->i, len), p)))
			return (r);
		if (rt == O_BRACE)
			p->level[1]++;
		if (rt == O_BRACKET)
			p->level[0]++;
		if (rt >= OR && rt <= O_BRACE)
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
		if ((ret = check_tok(s, p.i + p.len)) != NO_TOKEN)
		{
			if (ret == ESPACE)
				p.i = cut_space(s, p.i);
			else if ((ret_lex = choose_pars(lst, s, ret, &p)))
				return (return_new_prompt(ret_lex));
		}
	}
	sort_list_token(lst, compl, hist);
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	return (can_create_tree(*lst));
}
