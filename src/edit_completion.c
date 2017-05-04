/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:17:28 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:19:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			fill_command(t_slist **list, char *path)
{
	char			**bin_path;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	i = -1;
	if (!path)
		return (0);
	if (!(bin_path = ft_strsplit(path, ':')))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
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

int			insert_next(t_slist *tmp, char *s)
{
	t_slist		*tmp_next;

	while (tmp->next && ft_strcmp(tmp->next->s, s) < 0)
		tmp = tmp->next;
	if (ft_strcmp(tmp->s, s) && (!tmp->next || ft_strcmp(tmp->next->s, s)))
	{
		tmp_next = (tmp->next) ? tmp->next : NULL;
		if (!(tmp->next = create_sort_list(ft_strdup(s))))
			return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
		tmp->next->prev = tmp;
		tmp->next->next = tmp_next;
		if (tmp_next)
			tmp_next->prev = tmp->next;
	}
	return (0);
}

int			insert_in_list(t_slist **list, char *s)
{
	t_slist		*tmp;
	t_slist		*tmp_next;

	if (s && !*list)
	{
		if (!(*list = create_sort_list(ft_strdup(s))))
			return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	}
	else if (s)
	{
		tmp = *list;
		if (tmp && ft_strcmp(tmp->s, s) > 0)
		{
			if (!(tmp_next = create_sort_list(ft_strdup(s))))
				return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
			tmp_next->next = tmp;
			tmp->prev = tmp_next;
			*list = tmp_next;
		}
		else if (insert_next(tmp, s) == ERR_EXIT)
			return (ERR_EXIT);
	}
	return (0);
}

int			fill_variable(t_slist **list, t_core *core)
{
	t_elem		*tmp;

	tmp = (core->env) ? core->env->head : NULL;
	while (tmp)
	{
		if (insert_in_list(list, tmp->name) == ERR_EXIT)
			return (ERR_EXIT);
		tmp = tmp->next;
	}
	tmp = (core->exp) ? core->exp->head : NULL;
	while (tmp)
	{
		if (insert_in_list(list, tmp->name) == ERR_EXIT)
			return (ERR_EXIT);
		tmp = tmp->next;
	}
	tmp = (core->set) ? core->set->head : NULL;
	while (tmp)
	{
		if (insert_in_list(list, tmp->name) == ERR_EXIT)
			return (ERR_EXIT);
		tmp = tmp->next;
	}
	return (0);
}

int			init_completion(t_completion *cplt, t_core *core)
{
	char	*s;

	if (ft_find_elem("PATH", core->env) == NULL)
		s = NULL;
	else
		s = ft_find_elem("PATH", core->env)->value;
	if (cplt->command)
		destroy_sort_list(&(cplt->command));
	if (cplt->username)
		destroy_sort_list(&(cplt->username));
	if (cplt->hostname)
		destroy_sort_list(&(cplt->hostname));
	if (cplt->variable)
		destroy_sort_list(&(cplt->variable));
	if (fill_command(&(cplt->command), s) == ERR_EXIT)
		return (ERR_EXIT);
	if (fill_username(&(cplt->username), "/etc/passwd") == ERR_EXIT)
		return (ERR_EXIT);
	if (fill_hostname(&(cplt->hostname), "/etc/hosts") == ERR_EXIT)
		return (ERR_EXIT);
	if (fill_variable(&(cplt->variable), core) == ERR_EXIT)
		return (ERR_EXIT);
	return (0);
}
