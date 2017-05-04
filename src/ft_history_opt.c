/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:07:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Ft_check_histopt_arg est une fonction qui va servir de gestionnaire des
**	options qui prennent plusieurs arguments en parametre, elle va definir
**	s'ils s'agit de l'option 's' ou 'p', puis retourner la position dans args.
*/

int			ft_check_histopt_arg(t_lst *hist, char **args, int i)
{
	int		ret;

	if (args[i][1] == HIST_OPT_P)
	{
		if ((ret = ft_histopt_p(hist, &(args[i]))) == ERR_EXIT)
		{
			return (ERR_EXIT);
		}
		i += ret;
	}
	else if (args[i][1] == HIST_OPT_S)
	{
		if (ft_histopt_s(hist, &(args[i + 1])) == ERR_EXIT)
			return (ERR_EXIT);
		return (ERR_NEW_CMD);
	}
	return (i);
}

/*
**	Ft_check_histopt_file2 est la deuxieme partie de ft_check_histopt_file.
**	Se réferer a la premiere partie.
*/

static int	ft_check_histopt_file2(t_core *core, char **args, int j)
{
	int		ret;
	char	*filename;

	ret = 0;
	filename = (args[1]) ? args[1] : NULL;
	if (args[0][1] == HIST_OPT_R)
	{
		if ((ret = ft_histopt_r(core, filename)) != -1)
			return (j);
	}
	if (args[0][1] == HIST_OPT_W)
	{
		if ((ret = ft_histopt_w(core, filename)) != ERR_NEW_CMD)
			return (j);
	}
	if (args[0][1] == HIST_OPT_N)
	{
		if ((ret = ft_histopt_n(core, filename)) != ERR_NEW_CMD)
			return ((ret == ERR_EXIT) ? ERR_EXIT : j);
	}
	return ((ret < 0) ? ret : j);
}

/*
**	Ft_check_histopt_file est une fonction qui gere les options prenant
**	un nom de fichier optionnel en parametre, les options 'a', 'n', 'r' et 'w'
**	sont concernés, cette fonction sert de gestionnaire des fonctions envoyés.
*/

int			ft_check_histopt_file(t_core *core, char **args, int i)
{
	int		ret;
	int		j;
	char	*filename;

	filename = NULL;
	j = i;
	if (args[i + 1] != NULL && args[i + 1][0] != '-')
	{
		++j;
		filename = args[j];
	}
	if (args[i][1] == HIST_OPT_A)
	{
		if ((ret = ft_histopt_a(core, filename)) != ERR_NEW_CMD)
			return (j);
	}
	if ((ret = ft_check_histopt_file2(core, &(args[i]), j)) >= 0)
		return (j);
	return (ret);
}

/*
**	Ft_check_histopt est une fonction qui va servir de boucle d'options.
**	C'est elle qui gere l'appelle ou non des gestionnaires de ces dernieres.
*/

int			ft_check_histopt(t_core *core, char **args, int i)
{
	int		j;
	char	c;

	j = 0;
	while (args[i][++j])
	{
		c = args[i][j];
		if (c == HIST_OPT_C)
			core->hist = ft_histopt_c(core->hist);
		else if (c == HIST_OPT_D)
			return (ft_check_histopt_offset(core->hist, args, i));
		else if (c == HIST_OPT_P || c == HIST_OPT_S)
			return (ft_check_histopt_arg(core->hist, args, i));
		else if (c == HIST_OPT_A || c == HIST_OPT_N || c == HIST_OPT_R
				|| c == HIST_OPT_W)
			return (ft_check_histopt_file(core, args, i));
		else
			return (ft_print_histopt_err(args[i][j]));
	}
	return (i);
}

/*
**	Ft_parse_histopt va checker en boucle les argumets pour trouver des erreurs
**	ou renvoyer ft_check_histopt pour identifier la validité de ces dernieres.
*/

int			ft_parse_histopt(t_core *core, char **args)
{
	int		i;
	int		pos;

	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-')
		{
			if (args[i][1] == '-')
				return ((args[i][2]) ? ft_print_histopt_err(args[i][2]) : 0);
			else
			{
				pos = i;
				if ((pos = ft_check_histopt(core, args, pos)) < 0)
					return (pos);
			}
		}
		else
			break ;
		++i;
	}
	return (0);
}
