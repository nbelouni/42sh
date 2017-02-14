/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:23:32 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/08 18:21:10 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_builtin_echo(t_lst *env, char *cmd, char **args)
{
	char	*tmp;
	char	*output;

	(void)env;
	if (!cmd)
		return (-1);
	if (args && *args)
	{
		if (!(tmp = ft_tabconcat(args)))
			return (ERR_EXIT);
		if ((output = ft_epurstr(tmp)) == NULL)
			return (ERR_EXIT);
		write(1, output, ft_strlen(output));
		ft_strdel(&output);
		ft_strdel(&tmp);
	}
	write(1, "\n", 1);
	return (0);
}
