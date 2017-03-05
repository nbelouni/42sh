/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:23:32 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/05 13:51:13 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_builtin_echo est la seule fonction du builtin echo, elle gere
**	les erreurs, concat les arguments qu'elle reçoit en une string épurée
**	puis l'affiche.
*/

int		ft_builtin_echo(t_lst *env, char *cmd, char **args)
{
	char	*tmp;
	char	*output;

	(void)env;
	if (!cmd || !cmd[0])
		return (-1);
	if (args && *args)
	{
		if (!(tmp = ft_tabconcat(args)))
			return (ERR_EXIT);
		if ((output = ft_epurstr(tmp)) == NULL)
			return (ft_free_and_return(ERR_EXIT, tmp, NULL));
		write(1, output, ft_strlen(output));
		ft_multi_free(output, tmp, NULL, NULL);
	}
	write(1, "\n", 1);
	return (0);
}
