/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_buf_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 19:31:44 by alallema          #+#    #+#             */
/*   Updated: 2017/02/25 15:21:39 by nbelouni         ###   ########.fr       */
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

int			parse_list(t_token **list, char *s, t_pt *p)
{
	t_token	*new;
	t_word	*tmp;
	int		ret;

	tmp = NULL;
	if (!s)
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if ((ret = lex_buf(s, &tmp)))
	{
		ft_strdel(&s);
		return (ret);
	}
	if (!(new = ft_tokenew(tmp, p->type, s, p->level)))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(*list))
		*list = new;
	else
		ft_tokenpush(list, new);
	return (0);
}

int			check_fd_out(t_token **list, char *s, t_pt *p)
{
	int		ret;

	while (s[p->i + p->len] && ft_isdigit(s[p->i + p->len]) == 1)
		p->len++;
	if (p->len != 0)
	{
		p->type = FD_OUT;
		if ((ret = parse_list(list, ft_strsub(s, p->i, p->len), p)))
			return (ret);
		p->i = p->i + p->len;
		p->len = 0;
	}
	return (0);
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

int			cut_cmd(t_token **list, char *s, t_pt *p)
{
	int		j;
	int		ret;

	j = 0;
	ret = 0;
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
	{
		if ((ret = parse_list(list, ft_strsub(s, p->i, p->len), p)))
			return (ret);
	}
	p->i = p->i + p->len;
	p->len = 0;
	return (0);
}
