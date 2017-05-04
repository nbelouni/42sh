/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:07:40 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:01 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int					ft_env_binary(char **args)
{
	int	*opt;
	int	i;

	opt = NULL;
	if ((opt = ft_opt_parse(ENV_OPT, args + 1, 0, 1)) == NULL)
		return (0);
	if (opt[0] < 0)
	{
		(opt) ? free(opt) : 0;
		return (0);
	}
	i = opt[0];
	while (args[++i])
	{
		if (args[i] && !ft_strchr(args[i], '='))
		{
			(opt) ? free(opt) : 0;
			return (1);
		}
	}
	(opt) ? free(opt) : 0;
	return (0);
}
