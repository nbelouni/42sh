/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:21:39 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/16 19:32:52 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int	ft_exec_history(t_lst *set, t_lst *hist, char **args)
{
	int		ret;

	ret = 0;
	if (args != NULL && args[0] != NULL)
	{
		ret = (args[0][0] != '-') ? 1 : ft_parse_histopt(set, hist, args);
		if (ret == 0 || ret == ERR_NEW_CMD || ret == ERR_EXIT)
		{
			return (ret);
		}
		else
		{
			if (!ft_strisdigit(args[0]))
			{
				write(2, "history: ", 9);
				return (ft_print_error(args[0], ERR_NUM_ARG, ERR_NEW_CMD));
			}
			ft_print_history(hist, ft_atoi(args[0]) - 1);
		}
	}
	return (0);
}

int			ft_builtin_history(t_lst *set, t_lst *hist, char **args)
{
	int		hsize;
	int		ret;

	ret = 0;
	if (hist != NULL)
	{
		hsize = 0;
		if ((hsize = ft_get_hsize(set)) == 0)
		{
			return (ERR_NEW_CMD);
		}
		if (args == NULL || *args == NULL || **args == '\0')
		{
			ft_print_history(hist, hist->size);
		}
		else
		{
			ret = ft_exec_history(set, hist, args);
		}
	}
	return (ret);
}
