/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:27:26 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 16:16:41 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int	*set_opt(int *opt, char *list_opt, char c, int overwrite)
{
	int		pos;

	pos = 0;
	if (overwrite == 1)
		ft_memset(&(opt[1]), 0, sizeof(int) * ft_strlen(list_opt));
	while (list_opt[pos] != c)
		pos++;
	pos += 1;
	opt[pos] = 1;
	return (opt);
}

static int	find_opt(int *opt, char *list_opt, char *arg, int overwrite)
{
	int	i;

	i = 0;
	if (!arg[0] || arg[0] != '-' || (arg[0] == '-' && !arg[1]))
		return (0);
	if (arg[0] == '-' && arg[1] && arg[1] == '-' && !arg[2])
		return (2);
	while (arg[++i])
	{
		if (!ft_strchr(list_opt, arg[i]))
		{
			write(2, ": illegal option -- ", 20);
			write(2, &arg[i], 1);
			write(2, "\nUsage: [- ", 11);
			write(2, list_opt, ft_strlen(list_opt));
			write(2, "]\n", 2);
			return (-1);
		}
		else
			opt = set_opt(opt, list_opt, arg[i], overwrite);
	}
	return (1);
}

int			*ft_opt_parse(int *opt, char *opts, char **args, int overwrite)
{
	int	ret;

	if (!(opt = (int *)malloc(sizeof(int) * (ft_strlen(opts) + 1))))
		return ((int *)ERR_EXIT);
	ft_memset(opt, 0, sizeof(int) * ft_strlen(opts) + 1);
	while (args[opt[0]])
	{
		ret = find_opt(opt, opts, args[opt[0]], overwrite);
		if (ret == -1)
		{
			(opt) ? free(opt) : 0;
			return ((int *)-1);
		}
		else if (ret == 0)
			return (&(opt[0]));
		else if (ret == 2)
		{
			++opt[0];
			return (&(opt[0]));
		}
		opt[0]++;
	}
	return (opt);
}
