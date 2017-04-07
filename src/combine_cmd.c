/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:52:53 by alallema          #+#    #+#             */
/*   Updated: 2017/04/06 18:12:50 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

static char		*listiter_cmd(t_list *lst, char *(*f)(t_list *elem), int i)
{
	char	*s;
	char	*tmp;

	s = NULL;
	tmp = NULL;
	while (lst && f)
	{
		s = ft_fix_join(s, (*f)(lst->content));
		tmp = s;
		if (lst->next && i)
		{
			s = ft_strjoin(tmp, "| ");
			free(tmp);
		}
		lst = lst->next;
	}
	return (s);
}

char			*iter_iolist_cmd(t_list *io_list)
{
	return (listiter_cmd(io_list, (void *)copy_redir, 0));
}

static char		*iter_process_cmd(t_list *process_list)
{
	return (listiter_cmd(process_list, (void *)copy_process, 1));
}

char			*iter_cmd(t_node_p process_tree)
{
	char	*s;
	char	*tmp;

	s = NULL;
	if (process_tree->type == PROCESS)
		s = iter_process_cmd(process_tree->data);
	else
	{
		if (((t_condition_if_p)process_tree->data)->type == IF_OR)
			tmp = ft_strdup("|| ");
		else
			tmp = ft_strdup("&& ");
		s = ft_fix_join(iter_cmd(process_tree->left), tmp);
		tmp = s;
		s = ft_fix_join(tmp, iter_cmd(process_tree->right));
	}
	return (s);
}
