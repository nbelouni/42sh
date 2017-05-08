/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_histopt_filename.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:07:07 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/08 16:17:33 by maissa-b         ###   ########.fr       */
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

int			ft_histopt_n(t_core *core, char *filename)
{
	int		fd;
	char	*buf;

	if ((filename = ft_check_hist_filename(core, filename)) == NULL)
		return (ERR_NEW_CMD);
	if ((fd = open(filename, O_RDWR, 0666)) == -1)
		return (ft_print_error("history", ERR_NO_ACCESS, ERR_NEW_CMD));
	buf = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		if (ft_is_histcmd_read(core->hist, buf) == ERR_EXIT)
		{
			(buf) ? ft_strdel(&buf) : 0;
			return (ERR_EXIT);
		}
		(buf) ? ft_strdel(&buf) : 0;
	}
	return (0);
}

int			ft_histopt_w(t_core *core, char *filename)
{
	if ((filename = ft_check_hist_filename(core, filename)) == NULL)
	{
		return (ERR_NEW_CMD);
	}
	return (ft_set_history(core->hist, filename));
}

int			ft_histopt_a(t_core *core, char *filename)
{
	t_elem	*tmp;
	int		fd;

	fd = 0;
	if ((filename = ft_check_hist_filename(core, filename)) == NULL)
		return (ERR_NEW_CMD);
	if ((fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
		return (ft_print_error("history", ERR_NO_ACCESS, ERR_NEW_CMD));
	tmp = core->hist->head;
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

int			ft_histopt_r(t_core *core, char *filename)
{
	if ((filename = ft_check_hist_filename(core, filename)) == NULL)
	{
		return (ERR_NEW_CMD);
	}
	if ((core->hist = ft_get_history(core->hist, filename)) == NULL)
	{
		return (ERR_NEW_CMD);
	}
	return ((filename == NULL) ? 0 : 1);
}
