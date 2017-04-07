/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:39:46 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/20 15:57:27 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	replace_entry est une fonction qui va s'occuper de clear la ligne d'entree
**	et de put la nouvelle entree pointee par str.
*/

static void	replace_entry(t_buf *buf, char *str)
{
	int		i;

	i = buf->size;
	m_right(calc_len(buf, END));
	while (--i >= 0)
	{
		vb_del(buf, DEL);
	}
	if (str != NULL && str[0] != '\0')
	{
		i = -1;
		while (str[++i] != '\0')
		{
			vb_insert(buf, &(str[i]));
		}
	}
}

/*
**	ft_mv_down va permettre de definir l'entree suivante a partir d'une liste.
*/

static int	ft_mv_down(t_buf *buf, t_elem **elem, char *last_cmd)
{
	if ((*elem) == NULL)
	{
		replace_entry(buf, last_cmd);
	}
	else
	{
		replace_entry(buf, (*elem)->name);
	}
	return (0);
}

/*
**	ft_mv_up va permettre de definir l'entree precedente a partir d'une liste.
*/

static int	ft_mv_up(t_buf *buf, t_elem **elem, char **last_cmd)
{
	if ((*elem)->next == NULL)
	{
		if (*last_cmd != NULL)
			ft_strdel(last_cmd);
		if ((*last_cmd = ft_strdup(buf->line)) == NULL)
			return (ERR_EXIT);
	}
	replace_entry(buf, (*elem)->name);
	return (0);
}

/*
**	edit_history est une fonction qui va definir si l'input est la fleche up
**	ou down, et appeler la fonction adaptée. La position d'elem dans la liste
**	est definie par le pointeur sur la position courrante, definit dans buf.
*/

int			edit_history(t_buf *buf, t_lst *hist, int x)
{
	if (x == UP)
	{
		if (buf->cur_hist != hist->head)
			buf->cur_hist = (buf->cur_hist) ? buf->cur_hist->prev : hist->tail;
		if (ft_mv_up(buf, &(buf->cur_hist), &(buf->last_cmd)) == ERR_EXIT)
		{
			return (ERR_EXIT);
		}
	}
	if (x == DOWN)
	{
		if (buf->cur_hist != NULL)
			buf->cur_hist = buf->cur_hist->next;
		ft_mv_down(buf, &(buf->cur_hist), buf->last_cmd);
	}
	return (0);
}
