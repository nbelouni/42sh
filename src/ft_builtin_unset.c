/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:22:49 by dogokar           #+#    #+#             */
/*   Updated: 2017/03/20 17:43:10 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
 **    va suprimmer un variable dans n'importe quel list
 */

int		ft_unset(t_core *set, char **args)
{
	while (*args != NULL)
	{
		if (ft_strchr(*args, '=') != NULL)
			return (ft_print_error("unset: Not a valid identifier: ", *args, -1));
		if (ft_unsetenv(set->exp, *args) != 1)
			if (ft_unsetenv(set->set, *args) != 1)
				ft_unsetenv(set->env, *args);
		args++;
	}
	return (0);
}

int		ft_builtin_unset(t_core *set, char **args)
{
	int	*opt;
	int	ret;

	if (args == NULL || *args == NULL || **args == '\0')
		return (0);
	if ((opt = ft_opt_parse(UNSET_OPT, args, 0)) == NULL)
		return (ERR_EXIT);
	ret = ft_unset(set, &(args[opt[0]]));
	free(opt);
	return (ret);
}