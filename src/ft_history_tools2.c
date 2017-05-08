/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_tools2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 22:50:44 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/08 16:18:10 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Fonction qui va afficher l'historique sur la sortie standard, start definit
**	a partir de quel element, en partant de la fin de liste, l'affichage
**	s'effectue. Si la taille de la liste est en tant que start, l'element
**	de depart est la tete de liste.
*/

int			ft_truncate_histlist(t_lst *hist, size_t n)
{
	t_elem	*tmp;
	void	*prev_tmp;

	tmp = NULL;
	prev_tmp = NULL;
	if (n == 0)
	{
		ft_lstclr(hist);
	}
	else
	{
		if (n < hist->size)
		{
			tmp = ft_get_nelem(hist, (hist->size - n));
			while (tmp != NULL)
			{
				prev_tmp = tmp->prev;
				ft_del_elem(&tmp, hist);
				tmp = prev_tmp;
			}
		}
	}
	return (0);
}

/*
**	Partie 2 de ft_truncate_histfile, utilisée pour la norme.
**	Se referer à la premiere partie.
*/

static int	ft_truncate_histfile2(t_lst *tmp_hist, int n, int fd)
{
	int		i;
	t_elem	*tmp_elem;

	i = tmp_hist->size - n;
	tmp_elem = tmp_hist->head;
	while (tmp_elem != NULL)
	{
		if (--i < 0)
			ft_putendl_fd(tmp_elem->name, fd);
		tmp_elem = tmp_elem->next;
	}
	if (tmp_hist != NULL)
	{
		ft_lstclr(tmp_hist);
		free(tmp_hist);
		tmp_hist = NULL;
	}
	return (0);
}

/*
**	Ft_truncate_histfile va tronquer le fichier d'historique en partant
**	de la fin, par rapport a n. La méthode utilisée est de copier le contenu
**	du fichier dans une liste temporaire, puis copier les n derniers elements
**	de cette derniere dans le fichier en ecrasant les precedentes entrées.
*/

int			ft_truncate_histfile(char *filename, int n)
{
	int		fd;
	t_lst	*tmp;

	tmp = NULL;
	if ((tmp = ft_get_history(tmp, filename)) == NULL)
		return (ERR_EXIT);
	if (!tmp->head || (fd = open(filename, O_RDWR | O_TRUNC | O_APPEND, 0666)) == -1)
	{
		ft_del_list(tmp);
		return (ERR_NEW_CMD);
	}
	ft_truncate_histfile2(tmp, n, fd);
	close(fd);
	return (0);
}
