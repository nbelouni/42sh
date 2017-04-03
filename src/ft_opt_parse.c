/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:27:26 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/24 18:19:11 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Affiche le message d'erreur d'option
*/

static int	print_opt_err(char *opts, char c)
{
	write(2, "illegal option -- ", 18);
	write(2, &c, 1);
	write(2, "\nUsage: [- ", 11);
	write(2, opts, ft_strlen(opts));
	write(2, "]\n", 2);
	return (-1);
}

/*
**	met a 1 les options dans le meme ordre dans la chaine d'int que la chaine
**	d'options opts (la macro). Si overwrite vaut 1, toute les autres options
**	quelles soient a 1 ou 0 sont remit a 0.
*/

static int	*ft_set_opt(int *opt, char *opts, char c, size_t overwrite)
{
	size_t pos;

	pos = 0;
	if (overwrite == 1)
	{
		ft_memset(&(opt[1]), 0, (sizeof(int) * ft_strlen(opts)));
	}
	while (opts[pos] != c)
	{
		++pos;
	}
	++pos;
	opt[pos] = 1;
	return (opt);
}

/*
**	check tout d'abord si le format option est valide et/ou le format d'arret
**	des options est present. Si le caractere fait parti de la chaine d'options
**	opts, ft_set_opt la mettra a 1 dans la chaine d'int, sinon, une erreur
**	est renvoyée.
*/

static int	ft_is_opt(int *opt, char *opts, char *arg, size_t overwrite)
{
	int	i;

	i = 1;
	if (arg[0] != '-' || (arg[0] == '-' && arg[1] == '\0'))
	{
		return (0);
	}
	if (arg[1] == '-')
	{
		return ((arg[2] != '\0') ? print_opt_err(opts, arg[2]) : 2);
	}
	else
	{
		while (arg[i] != '\0')
		{
			if (ft_strchr(opts, arg[i]) == NULL)
			{
				return (print_opt_err(opts, arg[i]));
			}
			opt = ft_set_opt(opt, opts, arg[i], overwrite);
			++i;
		}
	}
	return (1);
}

/*
**	checker d'options, itere sur chaque string contenues dans args et retourne
**	la chaine d'option.
*/

static int	*ft_check_opt(int *opt, char *opts, char **args, size_t overwrite)
{
	int		i;

	i = -1;
	while (args[++i] != NULL)
	{
		opt[0] = ft_is_opt(opt, opts, args[i], overwrite);
		if (opt[0] == -1)
		{
			return (opt);
		}
		if (opt[0] == 0 || (opt[0] == 2))
			break ;
	}
	opt[0] = (opt[0] == 2) ? i + 1 : i;
	return (opt);
}

/*
**	cree et retourne le tableau d'int opt, si l'allocation echoue null est
**	retourne, si il n'y a pas d'arguments, opt[0] est instancie a 0, sinon
**	ft_opt_check est appelé afin de definir la position dans args où le
**	parsing d'option se finit, ou une erreur d'option.
*/

int			*ft_opt_parse(char *opts, char **args, size_t overwrite)
{
	int		*opt;
	size_t	i;
	size_t	len;

	opt = NULL;
	i = 0;
	len = ft_strlen(opts) + 1;
	if ((opt = (int *)malloc(sizeof(int) * (len + 1))) == NULL)
	{
		return (NULL);
	}
	while (i <= len)
	{
		opt[i] = 0;
		++i;
	}
	if (args == NULL || *args == NULL || **args == 0)
	{
		opt[0] = 0;
	}
	else
	{
		opt = ft_check_opt(opt, opts, args, overwrite);
	}
	return (opt);
}
