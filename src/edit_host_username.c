/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_host_username.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 22:45:36 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:19:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			edit_username_line(char **line)
{
	char	*new;
	int		i;

	new = NULL;
	i = -1;
	if (!*line)
		return (0);
	while ((*line)[++i] && (*line)[i] != ':')
		;
	if ((*line)[i])
	{
		if (!(new = ft_strsub(*line, 0, i)))
			return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	}
	if (*line)
		free(*line);
	*line = new;
	return (0);
}

int			fill_username(t_slist **list, char *path)
{
	int				fd;
	char			*line;

	line = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (ft_print_error("21sh: ", ERR_READ, ERR_EXIT));
	while (get_next_line(fd, &line) > 0)
	{
		if (edit_username_line(&line) == ERR_EXIT)
			return (ERR_EXIT);
		if (insert_in_list(list, line) == ERR_EXIT)
			return (ERR_EXIT);
		(line) ? ft_strdel(&line) : 0;
	}
	(line) ? ft_strdel(&line) : 0;
	close(fd);
	return (0);
}

int			edit_hostname_line(t_slist *list, char **line)
{
	char		**val;
	int			i;
	t_slist		*tmp;

	if (!(val = ft_strsplit(*line, ' ')))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	if (ft_tablen(val) != 2)
		return (0);
	tmp = list;
	i = 1;
	while (tmp)
	{
		if (!ft_strcmp(val[i], tmp->s))
		{
			i = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (*line)
		free(*line);
	if (!(*line = ft_strdup(val[i])))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	ft_tabdel(val);
	return (0);
}

int			fill_hostname(t_slist **list, char *path)
{
	int				fd;
	char			*line;

	line = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (ft_print_error("21sh: ", ERR_READ, ERR_EXIT));
	while (get_next_line(fd, &line) > 0)
	{
		if (edit_hostname_line(*list, &line) == ERR_EXIT)
			return (ERR_EXIT);
		if (insert_in_list(list, line) == ERR_EXIT)
			return (ERR_EXIT);
		(line) ? ft_strdel(&line) : 0;
	}
	(line) ? ft_strdel(&line) : 0;
	close(fd);
	return (0);
}
