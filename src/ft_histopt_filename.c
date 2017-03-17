/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_histopt_filename.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:55:55 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/15 18:48:38 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int	ft_is_histcmd_read(t_lst *hist, char *buf)
{
	t_elem	*new_elem;

	new_elem = NULL;
	if ((new_elem = ft_find_elem(buf, hist)) == NULL)
	{
		if ((new_elem = ft_init_elem()) == NULL)
			return (ERR_EXIT);
		ft_insert_elem(new_elem, hist);
		if ((new_elem->name = ft_strdup(buf)) == NULL)
			return (ERR_EXIT);
	}
	return (0);
}

int			ft_histopt_n(t_lst *set, t_lst *hist, char *filename)
{
	int		fd;
	char	*buf;

	if ((filename = ft_check_hist_filename(set, filename)) == NULL)
		return (ERR_NEW_CMD);
	if ((fd = open(filename, O_RDWR)) == -1)
		return (ft_print_error("history", ERR_NO_ACCESS, ERR_NEW_CMD));
	buf = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		if (ft_is_histcmd_read(hist, buf) == ERR_EXIT)
		{
			ft_strdel(&buf);
			return (ERR_EXIT);
		}
		ft_strdel(&buf);
	}
	return (0);
}

int			ft_histopt_w(t_lst *set, t_lst *hist, char *filename)
{
	if ((filename = ft_check_hist_filename(set, filename)) == NULL)
	{
		return (ERR_NEW_CMD);
	}
	return (ft_set_history(hist, filename));
}

int			ft_histopt_a(t_lst *set, t_lst *hist, char *filename)
{
	t_elem	*tmp;
	int		fd;

	fd = 0;
	if ((filename = ft_check_hist_filename(set, filename)) == NULL)
		return (ERR_NEW_CMD);
	if ((fd = open(filename, O_RDWR | O_CREAT | O_APPEND)) == -1)
		return (ft_print_error("history", ERR_NO_ACCESS, ERR_NEW_CMD));
	tmp = hist->head;
	while (tmp != NULL)
	{
		if (tmp->is_appended == 0)
		{
			ft_putendl_fd(tmp->name, fd);
			tmp->is_appended = 1;
		}
		tmp = tmp->next;
	}
	close(fd);
	return ((filename == NULL) ? 0 : 1);
}

int			ft_histopt_r(t_lst **hist, t_lst *set, char *filename)
{
	if ((filename = ft_check_hist_filename(set, filename)) == NULL)
	{
		return (ERR_NEW_CMD);
	}
	if ((*hist = ft_get_history(*hist, filename)) == NULL)
	{
		return (ERR_NEW_CMD);
	}
	return ((filename == NULL) ? 0 : 1);
}
