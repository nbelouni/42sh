/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_buf_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 19:31:44 by alallema          #+#    #+#             */
/*   Updated: 2017/02/18 16:29:29 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_pt		*reset_int_pt(void)
{
	t_pt	*pt;

	if (!(pt = ft_memalloc(sizeof(t_pt))))
		return (NULL);
	pt->i = 0;
	pt->len = 0;
	pt->type = 0;
	pt->level[0] = 0;
	pt->level[1] = 0;
	return (pt);
}

void		parse_list(t_token **list, char *s, t_pt *p)
{
	t_token	*new;

	new = ft_tokenew(p->type, s, p->level);
	if (!(*list))
		*list = new;
	else
		ft_tokenpush(list, new);
}

int			check_fd_out(t_token **list, char *s, t_pt *p)
{
	int		j;

	(void)list;
	j = 0;
	while (s[p->i + p->len] && ft_isdigit(s[p->i + p->len]) == 1)
		p->len++;
	if (p->len != 0)
	{
		p->type = FD_OUT;
		parse_list(list, ft_strsub(s, p->i, p->len), p);
		p->i = p->i + p->len;
		p->len = 0;
	}
	return (j);
}

static int	check_fd_in(char *s, t_pt *p)
{
	int		j;
	int		ret;
	int		ret2;

	j = 0;
	ret = is_redir(s, p->i + p->len);
	ret2 = is_agreg(s, p->i + p->len);
	if (ret != SR_DIR && ret != SL_DIR && ret2 != DIR_AMP)
		return (0);
	while (p->len - j > 0 && ft_isdigit(s[p->i + p->len - j - 1]) == 1)
		j++;
	if ((p->i + p->len - j) != 0 && s[p->i + p->len - j - 1] != ' ')
		return (0);
	return (j);
}

void		cut_cmd(t_token **list, char *s, t_pt *p)
{
	int		j;

	j = 0;
	p->i = cut_space(s, p->i);
	while (s[p->i + p->len] && check_tok(s, p->i + p->len) == NO_TOKEN)
	{
		cut_quote(s, p);
		p->len++;
	}
	if (check_fd_in(s, p) > 0)
		p->type = FD_IN;
	else
		p->type = CMD;
	if (p->len != 0)
		parse_list(list, ft_strsub(s, p->i, p->len), p);
	p->i = p->i + p->len;
	p->len = 0;
}
