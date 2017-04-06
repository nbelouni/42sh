/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 15:28:05 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/06 15:28:09 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		init_optstruct(t_opt *opt_struct)
{
	opt_struct->opt_char = 0;
	opt_struct->opt_res = 0;
	opt_struct->opt_ind = 1;
	opt_struct->opt_arg = NULL;
}

static int	is_optend(t_opt **st_opt, char **index_ptr, char **argv, int argc)
{
	(*st_opt)->opt_res = 0;
	if ((*st_opt)->opt_ind >= argc || \
		*((*index_ptr) = argv[(*st_opt)->opt_ind]) != '-')
	{
		(*index_ptr) = RESET;
		return (-1);
	}
	if ((*index_ptr)[1] && *(++(*index_ptr)) == '-')
	{
		++((*st_opt)->opt_ind);
		(*index_ptr) = RESET;
		return (-1);
	}
	return (0);
}

static int	opt_is_invalid(t_opt **st_opt, char *index, char *optstr)
{
	if ((*st_opt)->opt_char == (int)'-')
	{
		return (-1);
	}
	if (!(*index))
	{
		++((*st_opt)->opt_ind);
	}
	if (*optstr != ':')
	{
		write(2, &((*st_opt)->opt_char), 1);
		write(2, NOT_ARG_ERRSTR, ft_strlen(NOT_ARG_ERRSTR));
	}
	return (NOT_OPT);
}

static int	stop_optparse(t_opt *st_opt, char *prog, char **index, char *optstr)
{
	(*index) = RESET;
	if (*optstr == ':')
		return (NO_ARG);
	write(2, prog, ft_strlen(prog));
	write(2, ERR_ILLEGAL_OPT, ft_strlen(ERR_ILLEGAL_OPT));
	write(2, &(st_opt->opt_char), 1);
	write(2, "usage : [", 10);
	write(2, optstr, ft_strlen(optstr));
	write(2, "]\n", 2);
	return (NOT_OPT);
}

static void	no_optarg(t_opt **st_opt, char *index)
{
	(*st_opt)->opt_arg = NULL;
	if (!(*index))
		++((*st_opt)->opt_ind);
}

int			ft_getopt(int ac, char **av, char *ops, t_opt *st_opt)
{
	static char	*index = RESET;
	char		*ptr;

	if (st_opt->opt_res || !(*index))
	{
		if (is_optend(&st_opt, &index, av, ac) == -1)
			return (-1);
	}
	if ((st_opt->opt_char = (int)*index++) == (int)':' || \
		!(ptr = ft_strchr(ops, st_opt->opt_char)))
		return (opt_is_invalid(&st_opt, index, ops));
	if (*(++ptr) != ':')
		no_optarg(&st_opt, index);
	else
	{
		if (*index)
			st_opt->opt_arg = index;
		else if (ac <= ++(st_opt->opt_ind))
			return (stop_optparse(st_opt, av[0], &index, ops));
		else
			st_opt->opt_arg = av[st_opt->opt_ind];
		index = RESET;
		++(st_opt->opt_ind);
	}
	return (st_opt->opt_char);
}
