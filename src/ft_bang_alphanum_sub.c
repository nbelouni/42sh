/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bang_alphanum_sub.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 18:14:45 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/24 18:15:00 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		bang_number_sub(t_lst *hist, char **s, char *n)
{
	int		ret;
	int		number;
	char	*tmp;
	char	*tmp2;
	char	*tmpjoin;

	number = (n[0] == '-') ? hist->size - ft_atoi(n + 1) + 1 : ft_atoi(n);
	if ((tmp2 = ft_gets_hist_ncmd(hist, number)) == NULL)
		return (ft_print_error("42sh: !", ERR_EVENT_NFOUND, ERR_NEW_CMD));
	if ((tmpjoin = ft_strjoin("!", n)) == NULL)
		return (ERR_EXIT);
	tmp = *s;
	ret = 0;
	if ((*s = ft_strreplace(tmp, tmpjoin, tmp2)) == NULL)
		ret = ERR_NEW_CMD;
	(tmp2) ? ft_strdel(&tmp2) : 0;
	(tmp) ? ft_strdel(&tmp) : 0;
	(tmpjoin) ? ft_strdel(&tmpjoin) : 0;
	return (ret);
}

int		bang_start_occur_sub(t_lst *hist, char **s, char *n)
{
	int		ret;
	char	*tmp;
	char	*tmp2;
	char	*tmpjoin;

	if ((tmp2 = ft_gets_in_hist(hist, n, &ft_strncmp_bis)) == NULL)
		return (ft_print_error("42sh: !", ERR_EVENT_NFOUND, ERR_NEW_CMD));
	if ((tmpjoin = ft_strjoin("!", n)) == NULL)
		return (ERR_EXIT);
	tmp = *s;
	ret = 0;
	if ((*s = ft_strreplace(tmp, tmpjoin, tmp2)) == NULL)
		ret = ERR_NEW_CMD;
	(tmp) ? ft_strdel(&tmp) : 0;
	(tmpjoin) ? ft_strdel(&tmpjoin) : 0;
	(tmp2) ? ft_strdel(&tmp2) : 0;
	return (ret);
}

int		bang_contain_occur_sub(t_lst *hist, char **s, char *n)
{
	int		ret;
	char	*tmp;
	char	*tmp2;
	char	*tmpjoin;

	if ((tmp2 = ft_gets_in_hist(hist, n, &ft_strstr_bis)) == NULL)
		return (ft_print_error("42sh: !", ERR_EVENT_NFOUND, ERR_NEW_CMD));
	if ((tmpjoin = ft_strjoin("!?", n)) == NULL)
		return (ERR_EXIT);
	tmp = *s;
	ret = 0;
	if ((*s = ft_strreplace(tmp, tmpjoin, tmp2)) == NULL)
		ret = ERR_NEW_CMD;
	(tmp) ? ft_strdel(&tmp) : 0;
	(tmpjoin) ? ft_strdel(&tmpjoin) : 0;
	(tmp2) ? ft_strdel(&tmp2) : 0;
	return (ret);
}
