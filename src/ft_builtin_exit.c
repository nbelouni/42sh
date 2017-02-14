/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:21:52 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 18:05:47 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_builtin_exit(t_lst *env, char *cmd, char **args)
{
	int	ret;

	ret = 0;
	if (args && args[0])
	{
		if (!ft_isdigit(args[0][0]) || args[1])
			return (ft_print_error(cmd, ERR_EXPR_SYNT, ERR_NEW_CMD));
		else if (!ft_strisdigit(args[0]) && args[0][0] != '-')
			return (ft_print_error(cmd, ERR_EXT_FRMT, ERR_NEW_CMD));
		ret = (unsigned char)ret;
		ret = ft_atoi(args[0]);
	}
	ft_del_list(env);
	exit(ret);
	return (ret);
}
