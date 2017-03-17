/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:46:55 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/17 15:25:06 by maissa-b         ###   ########.fr       */
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

static int	ft_truncate_histfile2(t_lst *tmp_hist, int n, int fd)
{
	int		i;
	t_elem	*tmp_elem;

	i = tmp_hist->size - n;
	tmp_elem = tmp_hist->head;
	while (tmp_elem != NULL)
	{
		if (--i <= 0)
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

int			ft_truncate_histfile(char *filename, int n)
{
	int		fd;
	t_lst	*tmp_hist;

	tmp_hist = NULL;
	if ((tmp_hist = ft_get_history(tmp_hist, filename)) == NULL)
		return (ERR_EXIT);
	if (tmp_hist->head == NULL)
	{
		free(tmp_hist);
		return (ERR_NEW_CMD);
	}
	if ((fd = open(filename, O_RDWR | O_TRUNC | O_APPEND)) == -1)
	{
		ft_del_list(tmp_hist);
		return (ERR_NEW_CMD);
	}
	ft_truncate_histfile2(tmp_hist, n, fd);
	close(fd);
	return (0);
}

char		*ft_get_hfname(t_lst *set)
{
	t_elem	*elem;

	elem = NULL;
	if ((elem = ft_find_elem("HISTFILE", set)) == NULL)
	{
		return (NULL);
	}
	if (elem->value == NULL || elem->value[0] == '\0')
	{
		return (NULL);
	}
	return (elem->value);
}

int			ft_check_history_var(t_lst *set, t_lst *hist)
{
	int		hsize;
	int		hfsize;
	char	*hfname;

	if ((hsize = ft_get_hsize(set)) >= 0)
	{
		ft_truncate_histlist(hist, (size_t)hsize);
	}
	if ((hfname = ft_get_hfname(set)) != NULL)
	{
		if ((hfsize = ft_get_hfsize(set)) >= 0)
		{
			if ((hsize = ft_truncate_histfile(hfname, hfsize)) < 0)
			{
				return (hsize);
			}
		}
	}
	return (0);
}

int			ft_cmd_to_history(t_lst *hist, char *cmd)
{
	t_elem	*new_elem;

	new_elem = NULL;
	if ((new_elem = ft_init_elem()) == NULL)
	{
		return (ERR_EXIT);
	}
	if ((new_elem->name = ft_strdup(cmd)) == NULL)
	{
		return (ERR_EXIT);
	}
	ft_insert_elem(new_elem, hist);
	return (0);
}

static int	ft_intlen(int n)
{
	int		i;
	int		count;

	count = 0;
	i = n;
	while (i != 0)
	{
		i /= 10;
		++count;
	}
	return (count);
}

static void	ft_putnchar(char c, int n)
{
	int		i;

	i = -1;
	while (++i != n)
	{
		write(1, &c, 1);
	}
}

int			ft_print_history(t_lst *hist, int start)
{
	int		i;
	t_elem	*tmp;

	if (start < 0)
		return (0);
	if (start >= (int)hist->size)
		tmp = hist->head;
	else
		tmp = ft_get_nelem(hist, (hist->size - start));
	i = (tmp == hist->head) ? 1 : (hist->size - start);
	while (tmp != NULL)
	{
		if (tmp->name != NULL && tmp->name[0] != '\0')
		{
			ft_putnbr(i);
			(tmp->is_modified == 1) ? write(1, "*", 1) : 0;
			ft_putnchar(' ', (7 - ft_intlen(i)));
			ft_putendl_fd(tmp->name, 1);
		}
		tmp = tmp->next;
		++i;
	}
	return (0);
}

/*
**	Fonction utilisee lorsque une autre fonction liee a l'historique a besoin
**	de verifier si filename est NULL, auquel cas HISTFILE est recherche dans
**	le set et le pointeur sur filename pointe sur la value, si elle existe,
**	de la variable HISTFILE, sinon NULL est retourne.
*/

char		*ft_check_hist_filename(t_lst *set, char *filename)
{
	t_elem	*elem;

	if (filename == NULL || filename[0] == '\0')
	{
		if ((elem = ft_find_elem("HISTFILE", set)) == NULL)
		{
			return (NULL);
		}
		if (elem->value == NULL || elem->value[0] == '\0')
		{
			return (NULL);
		}
		filename = elem->value;
	}
	return (filename);
}
