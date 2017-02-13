/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:22:07 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/12 18:55:55 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_setenv(t_lst *env, char *var, char *word)
{
	t_elem	*tmp;

	if ((tmp = ft_find_elem(var, env)) == NULL)
	{
		if (!(tmp = ft_init_elem()))
			return (ERR_EXIT);
		ft_add_elem(tmp, env);
		tmp->name = ft_strdup(var);
	}
	else
	{
		if (tmp->value != NULL)
			ft_strdel(&tmp->value);
	}
	tmp->value = (word != NULL) ? ft_strdup(word) : NULL;
	return (0);
}

int		ft_builtin_setenv(t_lst *env, char *cmd, char **args)
{
	if (!args[0])
		ft_print_lst(env);
	else
	{
		if (ft_strchr(args[0], '='))
			return (ft_print_error(cmd, ERR_VAR_NO_ALPHA, ERR_NEW_CMD));
		else if (!ft_isalpha(args[0][0]))
			return (ft_print_error(cmd, ERR_VAR_BEG_NO_ALPHA, ERR_NEW_CMD));
		else
		{
			if (args[1] && args[2])
				return (ft_print_error(cmd, ERR_TOO_MANY_ARGS, ERR_NEW_CMD));
			ft_setenv(env, args[0], args[1]);
		}
	}
	return (0);
}
