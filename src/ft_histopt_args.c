/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_histopt_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:59:29 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/29 13:03:03 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_histopt_p est la fonction qui va gerer le comportement de l'option 'p'
**	du builtin history, qui est de simplement afficher la substitution
**	des arguments sans stocker la commande dans l'historique.
*/

int		ft_histopt_p(t_lst *hist, char **args)
{
	int		i;
	char	*tmp;
	t_elem	*tmp_tail;

	i = 0;
	tmp_tail = hist->tail;
	if (args && args[1])
	{
		while (args[++i] != NULL)
		{
			tmp = NULL;
			if ((tmp = ft_strtrim(args[i])) == NULL)
			{
				return (ERR_EXIT);
			}
			ft_putendl_fd(tmp, 1);
			(tmp) ? ft_strdel(&tmp) : 0;
		}
		ft_del_elem(&tmp_tail, hist);
	}
	return (i);
}

/*
**	ft_histopt_s est la fonction qui gere le comportement de l'option 's'
**	du builtin history, qui est de sauvegarder args dans l'historique sans
**	stocker la commande elle meme.
*/

int		ft_histopt_s(t_lst *hist, char **args)
{
	t_elem	*elem;

	elem = hist->tail;
	ft_del_elem(&elem, hist);
	if ((elem = ft_init_elem()) == NULL)
		return (ERR_EXIT);
	if ((elem->name = ft_tabconcat(args)) == NULL)
		return (ERR_EXIT);
	ft_insert_elem(elem, hist);
	return (0);
}
