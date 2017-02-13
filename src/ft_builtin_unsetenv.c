/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:22:01 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 17:38:23 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_unsetenv(t_lst *env, char *var)
{
	t_elem	*elem;

	if ((elem = ft_find_elem(var, env)) == NULL)
		return (-1);
	ft_del_elem(&elem, env);
	return (0);
}

int		ft_builtin_unsetenv(t_lst *env, char *cmd, char **args)
{
	int	i;

	i = 0;
	if (args == NULL || args[0] == NULL)
	{
		return (ft_print_error(cmd, ERR_TOO_FEW_ARGS, ERR_NEW_CMD));
	}
	while (env && args[i] && args[i][0])
	{
		ft_unsetenv(env, args[i]);
		i++;
	}
	return (0);
}
