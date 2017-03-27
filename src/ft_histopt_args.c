/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_histopt_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:59:29 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/16 19:18:44 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_histopt_p(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[++i] != NULL)
	{
		tmp = NULL;
		if ((tmp = ft_strtrim(args[i])) == NULL)
		{
			return (ERR_EXIT);
		}
		ft_putendl_fd(tmp, 1);
		ft_strdel(&tmp);
	}
	return (i);
}

int		ft_histopt_s(t_lst *hist, char **args)
{
	t_elem	*elem;

	elem = hist->tail;
	ft_del_elem(&elem, hist);
	if ((elem = ft_init_elem()) == NULL)
		return (ERR_EXIT);
	if ((elem->name = ft_tabconcat(args)) == NULL)
		return (ERR_EXIT);
	ft_insert_elem(elem, hist);
	return (0);
}
