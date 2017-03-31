/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:22:01 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/29 14:51:42 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_unsetenv est appelée afin de supprimer de la liste les elements dont
**	la variable name, contenue dans ces derniers, a pour valeur var.
*/

int		ft_unsetenv(t_lst *env, char *var)
{
	t_elem	*elem;

	elem = NULL;
	if ((elem = ft_find_elem(var, env)) != NULL)
	{
		ft_del_elem(&elem, env);
		return (1);
	}
	return (0);
}

/*
**	la fonction ft_builtin_unsetenv gere la seule erreur (pas d'arguments)
**	et appelle la fonction ft_unsetenv en boucle sur les arguments args.
*/

int		ft_builtin_unsetenv(t_core *core, char **args)
{
	int	i;

	i = 0;
	if (args == NULL || args[0] == NULL)
	{
		return (ft_print_error("unsetenv", ERR_TOO_FEW_ARGS, ERR_NEW_CMD));
	}
	if (core->env != NULL)
	{
		while (core->env != NULL && args[i] != NULL && args[i][0] != '\0')
		{
			ft_unsetenv(core->env, args[i]);
			++i;
		}
	}
	return (0);
}
