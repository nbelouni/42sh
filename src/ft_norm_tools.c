/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 20:05:40 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 20:09:47 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_pwd_swap(t_lst *env, char *owd, char *cwd)
{
	t_elem		*elem;

	if ((elem = ft_find_elem("PWD", env)) != NULL)
		(elem->value && elem->value[0]) ? ft_strdel(&(elem->value)) : 0;
	else
	{
		if (!(elem = ft_init_elem()))
			return (ERR_EXIT);
		ft_add_elem(elem, env);
		elem->name = ft_strdup("PWD");
	}
	elem->value = (cwd && cwd[0]) ? ft_strdup(cwd) : NULL;
	if ((elem = ft_find_elem("OLDPWD", env)) != NULL)
		(elem->value && elem->value[0]) ? ft_strdel(&(elem->value)) : 0;
	else
	{
		if (!(elem = ft_init_elem()))
			return (ERR_EXIT);
		ft_add_elem(elem, env);
		elem->name = ft_strdup("OLDPWD");
	}
	elem->value = (owd && owd[0]) ? ft_strdup(owd) : NULL;
	return (0);
}

void	ft_del_list(t_lst *lst)
{
	t_elem	*head;
	t_elem	*tmp;

	head = lst->head;
	while (head != NULL)
	{
		tmp = head->next;
		ft_del_elem(&head, lst);
		head = tmp;
	}
	ft_memset(lst, 0, sizeof(t_lst));
	free(lst);
}
