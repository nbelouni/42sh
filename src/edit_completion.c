/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:17:28 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 19:07:53 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			fill_command(t_list **list, char *path)
{
	char			**bin_path;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	i = -1;
	if (!(bin_path = ft_strsplit(path, ':')))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	while (bin_path[++i])
	{
		if ((dirp = opendir(bin_path[i])) != NULL)
		{
			while ((dp = readdir(dirp)) != NULL)
			{
				if (insert_in_list(list, dp->d_name) == ERR_EXIT)
					return (ERR_EXIT);
			}
			closedir(dirp);
		}
	}
	ft_tabdel(bin_path);
	return (0);
}

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
			return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	}
	if (*line)
		free(*line);
	*line = new;
	return (0);
}

int			insert_next(t_list *tmp, char *s)
{
	t_list		*tmp_next;

	while (tmp->next && ft_strcmp(LIST_S(tmp->next), s) < 0)
		tmp = tmp->next;
	if (ft_strcmp(LIST_S(tmp), s) && (!tmp->next || ft_strcmp(LIST_S(tmp->next), s)))
	{
		tmp_next = (tmp->next) ? tmp->next : NULL;
		if (!(tmp->next = ft_lstnew(s, sizeof(char) * (ft_strlen(s) + 1))))
			return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
		tmp->next->prev = tmp;
		tmp->next->next = tmp_next;
		if (tmp_next)
			tmp_next->prev = tmp->next;
	}
	return (0);
}

int			insert_in_list(t_list **list, char *s)
{
	t_list		*tmp;
	t_list		*tmp_next;

	if (s && !*list)
	{
		if (!(*list = ft_lstnew(s, sizeof(char) * (ft_strlen(s) + 1))))
			return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	}
	else if (s)
	{
		tmp = *list;
		if (tmp && ft_strcmp(LIST_S(tmp), s) > 0)
		{
			if (!(tmp_next = ft_lstnew(s, sizeof(char) * (ft_strlen(s) + 1))))
				return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
			tmp_next->next = tmp;
			tmp->prev = tmp_next;
			*list = tmp_next;
		}
		else if (insert_next(tmp, s) == ERR_EXIT)
			return (ERR_EXIT);
	}
	return (0);
}

int			fill_username(t_list **list, char *path)
{
	int				fd;
	char			*line;

	line = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (ft_print_error("42sh: ", ERR_READ, ERR_EXIT));
	while (get_next_line(fd, &line) > 0)
	{
		if (edit_username_line(&line) == ERR_EXIT)
			return (ERR_EXIT);
		if (insert_in_list(list, line) == ERR_EXIT)
			return (ERR_EXIT);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (line)
		free(line);
	close(fd);
	return (0);
}

int			edit_hostname_line(t_list *list, char **line)
{
	char	**val;
	int		i;
	t_list	*tmp;

	if (!(val = ft_strsplit(*line, ' ')))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	if (ft_tablen(val) != 2)
		return (0);
	PUT2("val[0] : ");PUT2(val[0]);X('\n');
	PUT2("val[1] : ");PUT2(val[1]);X('\n');
	tmp = list;
	i = 1;
	while (tmp)
	{
		if (!ft_strcmp(val[i], LIST_S(tmp)))
		{
			i = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (*line)
		free(*line);
	if (!(*line = ft_strdup(val[i])))
		return (ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	ft_tabdel(val);
	return (0);
}

int			fill_hostname(t_list **list, char *path)
{
	int		fd;
	char	*line;

	line = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (ft_print_error("42sh: ", ERR_READ, ERR_EXIT));
	while (get_next_line(fd, &line) > 0)
	{
		if (edit_hostname_line(*list, &line) == ERR_EXIT)
			return (ERR_EXIT);
		if (insert_in_list(list, line) == ERR_EXIT)
			return (ERR_EXIT);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (line)
		free(line);
	close(fd);
	return (0);
}

int			fill_variable(t_list **list, t_elem *env)
{
	t_elem		*tmp;

	tmp = env;
	while (tmp)
	{
		if (insert_in_list(list, tmp->name) == ERR_EXIT)
			return (ERR_EXIT);
		tmp = tmp->next;
	}
	return (0);
}

int			init_completion(t_completion *cplt, t_lst *env)
{
	char	*s;

	s = ft_find_elem("PATH", env)->value;
	if (fill_command(&(cplt->command), s) == ERR_EXIT)
		return (ERR_EXIT);
	if (fill_username(&(cplt->username), "/etc/passwd") == ERR_EXIT)
		return (ERR_EXIT);
	if (fill_hostname(&(cplt->hostname), "/etc/hosts") == ERR_EXIT)
		return (ERR_EXIT);
	if (fill_variable(&(cplt->variable), env->head) == ERR_EXIT)
		return (ERR_EXIT);
	return (0);
}
