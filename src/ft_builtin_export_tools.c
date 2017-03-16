/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:19:12 by dogokar           #+#    #+#             */
/*   Updated: 2017/03/15 18:19:59 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		move_to_env(t_elem *lst, t_lst *env, t_lst *type_env)
{
	ft_extract_elem(&lst, type_env);
	ft_insert_elem(lst, env);
}

int			ft_add_elemo(t_lst *lst, char *s)
{
	t_elem	*elem;

	elem = NULL;
	if (s && s[0])
	{
		if ((elem = ft_init_elem()) == NULL)
			return (ERR_EXIT);
		elem->name = ft_strdup(s);
		ft_insert_elem(elem, lst);
		return (0);
	}
	return (-1);
}
