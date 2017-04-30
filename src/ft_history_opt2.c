/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_opt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 22:45:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/30 22:50:21 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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
