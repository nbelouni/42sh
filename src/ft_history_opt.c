/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:49:22 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/20 14:28:19 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Option c du builtin history, clear la liste hist si elle n'est pas NULL.
*/

t_lst		*ft_histopt_c(t_lst *hist)
{
	if (hist != NULL && hist->head != NULL && hist->size > 0)
	{
		ft_lstclr(hist);
	}
	return (hist);
}

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
**	Ft_check_histopt_offset est une fonction qui gere les options prenant
**	un digit en parametre, ici seule l'option 'd' est concernee.
*/

int			ft_check_histopt_offset(t_lst *hist, char **args, int i)
{
	if (ft_histopt_d(hist, args[i + 1]) == ERR_NEW_CMD)
	{
		i = ERR_NEW_CMD;
	}
	else
	{
		i += 1;
	}
	return (i);
}

/*
**	Ft_check_histopt_file2 est la deuxieme partie de ft_check_histopt_file.
**	Se réferer a la premiere partie.
*/

static int	ft_check_histopt_file2(t_lst *set, t_lst *hist, char **args, int j)
{
	int		ret;
	char	*filename;

	ret = 0;
	filename = (args[1]) ? args[1] : NULL;
	if (args[0][1] == HIST_OPT_R)
	{
		if ((ret = ft_histopt_r(&hist, set, filename)) != ERR_NEW_CMD)
			return (j);
	}
	if (args[0][1] == HIST_OPT_W)
	{
		if ((ret = ft_histopt_w(set, hist, filename)) != ERR_NEW_CMD)
			return (j);
	}
	if (args[0][1] == HIST_OPT_N)
	{
		if ((ret = ft_histopt_n(set, hist, filename)) != ERR_NEW_CMD)
			return ((ret == ERR_EXIT) ? ERR_EXIT : j);
	}
	return ((ret < 0) ? ret : j);
}

/*
**	Ft_check_histopt_file est une fonction qui gere les options prenant
**	un nom de fichier optionnel en parametre, les options 'a', 'n', 'r' et 'w'
**	sont concernés, cette fonction sert de gestionnaire des fonctions envoyés.
*/

int			ft_check_histopt_file(t_lst *set, t_lst *hist, char **args, int i)
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
		if ((ret = ft_histopt_a(set, hist, filename)) != ERR_NEW_CMD)
			return (j);
	}
	if ((ret = ft_check_histopt_file2(set, hist, &(args[i]), j)) >= 0)
		return (j);
	return (ret);
}

/*
**	Ft_check_histopt est une fonction qui va servir de boucle d'options.
**	C'est elle qui gere l'appelle ou non des gestionnaires de ces dernieres.
*/

int			ft_check_histopt(t_lst *set, t_lst *hist, char **args, int i)
{
	int		j;
	char	c;

	j = 0;
	while (args[i][++j])
	{
		c = args[i][j];
		if (c == HIST_OPT_C)
			hist = ft_histopt_c(hist);
		else if (c == HIST_OPT_D)
			return (ft_check_histopt_offset(hist, args, i));
		else if (c == HIST_OPT_P || c == HIST_OPT_S)
			return (ft_check_histopt_arg(hist, args, i));
		else if (c == HIST_OPT_A || c == HIST_OPT_N || c == HIST_OPT_R
				|| c == HIST_OPT_W)
			return (ft_check_histopt_file(set, hist, args, i));
		else
			return (ft_print_histopt_err(args[i][j]));
	}
	return (i);
}

/*
**	Ft_parse_histopt va checker en boucle les argumets pour trouver des erreurs
**	ou renvoyer ft_check_histopt pour identifier la validité de ces dernieres.
*/

int			ft_parse_histopt(t_lst *set, t_lst *hist, char **args)
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
				if ((pos = ft_check_histopt(set, hist, args, pos)) < 0)
					return (pos);
			}
		}
		else
			break ;
		++i;
	}
	return (0);
}

/*
**	Print le message d'erreur des options invalides.
*/

int			ft_print_histopt_err(char c)
{
	write(2, "history: ", 9);
	write(2, &c, 1);
	write(2, ": invalid option \nhistory: usage: history [-c] [-d offset] [n] \
or history -awrn [filename] or history -ps arg [arg...]\n", 121);
	return (-1);
}
