/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:08:17 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:01 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_builtin_echo est la seule fonction du builtin echo, elle gere
**	les erreurs, concat les arguments qu'elle reçoit en une string épurée
**	puis l'affiche.
*/

int		ft_builtin_echo(t_core *core, char **args)
{
	char	*tmp;
	char	*output;

	(void)core;
	if (args && args[0])
	{
		if ((tmp = ft_tabconcat(args)) == NULL)
			return (ERR_EXIT);
		if ((output = ft_epurstr(tmp)) == NULL)
			return (ft_free_and_return(ERR_EXIT, tmp, NULL, NULL));
		write(1, output, ft_strlen(output));
		ft_multi_free(output, tmp, NULL, NULL);
	}
	write(1, "\n", 1);
	return (0);
}
