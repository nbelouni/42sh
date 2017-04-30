/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_dup_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 22:44:03 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/30 22:44:52 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_env_to_tab creer un tableau de strings contenant la liste d'env
**	pointé par g_set->env, puis le retourne contenant des strings de format
**	<name> + = + <value>.
*/

char	*ft_envv_to_str(t_elem *elem)
{
	size_t		name_len;
	char		*res;

	name_len = ft_strlen(elem->name);
	if ((res = ft_strnew(name_len + ft_strlen(elem->value) + 1)) == NULL)
	{
		return (NULL);
	}
	ft_strncpy(res, elem->name, ft_strlen(elem->name));
	res[name_len] = '=';
	if (elem->value)
		res = ft_strcat(res, elem->value);
	return (res);
}

char		**ft_env_to_tab(t_lst *lst)
{
	t_elem		*tmp;
	char		**res;
	size_t		i;

	res = NULL;
	if ((res = (char **)malloc(sizeof(char *) * (lst->size + 1))) == NULL)
	{
		return (NULL);
	}
	ft_memset(res, 0, (sizeof(char *) * (lst->size + 1)));
	tmp = lst->head;
	i = 0;
	while (tmp != NULL)
	{
		if ((res[i] = ft_envv_to_str(tmp)) == NULL)
		{
			ft_tabdel(res);
			return (NULL);
		}
		++i;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

/*
**	ft_env_to_list cree une liste depuis envp et la stock a l'adress
**	de g_set->env, elle ne check pas envp, on assume qu'il n'est pas vide.
*/

t_lst		*ft_env_to_list(char **envp, t_lst *lst)
{
	int			ret;

	if ((lst = ft_init_list()) == NULL)
	{
		return (NULL);
	}
	ret = 0;
	if (*envp != NULL)
	{
		while (*envp != NULL)
		{
			if ((ret = ft_add_elem(lst, *envp)) != 0)
			{
				if (ret == ERR_EXIT)
				{
					(lst) ? ft_del_list(lst) : 0;
				}
				return (NULL);
			}
			++envp;
		}
	}
	return (lst);
}
