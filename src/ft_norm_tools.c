/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 20:05:40 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/28 16:03:48 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Ft_modify_env est appelée par ft_pwd_swap, cette fonction sert a
**	soit creer, soit modifier la variable name dans l'environnement,
**	et lui attribuer la valeur value
*/

int		ft_modify_env(t_lst *env, char *name, char *value)
{
	t_elem	*elem;

	elem = NULL;
	if (name == NULL || name[0] == '\0')
		return (-1);
	if ((elem = ft_find_elem(name, env)) != NULL)
	{
		if (elem->value != NULL && elem->value[0] != '\0')
			ft_strdel(&(elem->value));
	}
	else
	{
		if ((elem = ft_init_elem()) == NULL)
			return (ERR_EXIT);
		ft_insert_elem(elem, env);
		if ((elem->name = ft_strdup(name)) == NULL)
			return (ERR_EXIT);
	}
	if (value && value[0])
	{
		if ((elem->value = ft_strdup(value)) == NULL)
			return (ERR_EXIT);
	}
	return (0);
}

/*
**	Ft_pwd_swap va simplement modifier l'environnement concernant le pwd
**	et l'oldpwd, cette fonction est appelée a chaque changements via chdir.
*/

int		ft_pwd_swap(t_lst *env, char *owd, char *cwd)
{
	int		ret;

	ret = 0;
	if ((ret = ft_modify_env(env, "PWD", cwd)) != 0)
	{
		return (ret);
	}
	if ((ret = ft_modify_env(env, "OLDPWD", owd)) != 0)
	{
		 return (ret);
	}
	return (0);
}

/*
**	Ft_del_list est une fonction qui va detruire entierement le contenu
**	de lst ainsi que liberer le pointeur, puis le mettre a NULL.
*/

void	ft_del_list(t_lst *lst)
{
	t_elem	*head;
	t_elem	*tmp;

	head = lst->head;
	while (head != NULL)
	{
		tmp = head->next;
		if (head != NULL)
		{
			ft_del_elem(&head, lst);
		}
		head = tmp;
	}
	ft_memdel((void *)&lst);
}
