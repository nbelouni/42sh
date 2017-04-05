/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_for_job.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:03:43 by alallema          #+#    #+#             */
/*   Updated: 2017/04/05 16:52:15 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

char	*iter_iolist_cmd(t_list *io_list);

static t_redir		(tab_redir[7]) = {
	[0] = { "< ", O_RDONLY},
	[1] = { "> ", O_WRONLY | O_CREAT | O_TRUNC},
	[2] = { "<< ", 0},
	[3] = { ">> ", O_WRONLY | O_CREAT | O_APPEND},
	[4] = { "<> ", O_RDWR | O_CREAT},
	[5] = { "<& ", O_RDWR},
	[6] = { ">& ", O_RDWR},
};

static char			*ft_fix_join(char *s, char *buf)
{
	char			*tmp;

	tmp = s;
	s = ft_strjoin(tmp, buf);
	free(tmp);
	free(buf);
	return (s);
}

char	*copy_redir(t_io *io)
{
	char	*s;
	int		i;

	i = 0;
	s = NULL;
	if (io->str && io->mode)
	{
		while (i < 7)
		{
			if (io->mode == tab_redir[i].mode)
				s = ft_strjoin(tab_redir[i].redir, io->str);
			i++;
		}
	}
	s = ft_fix_join(s, ft_strdup(" "));
	return (s);
}


char	*copy_process(t_process_p process)
{
	int		i;
	int		len;
	char	*s;
	char	*tmp;

	i = 0;
	len = 0;
	s = NULL;
	while (process->argv && process->argv[i])
	{
		tmp = s;
		s = ft_strjoin(tmp, process->argv[i]);
		free(tmp);
		tmp = s;
		s = ft_strjoin(tmp, " ");
		free(tmp);
		i++;
	}
	s = ft_fix_join(s, iter_iolist_cmd(process->ioList));
	return (s);
}

char	*listiter_cmd(t_list *lst, char *(*f)(t_list *elem), int i)
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

char	*iter_iolist_cmd(t_list *io_list)
{
	return(listiter_cmd(io_list, (void *)&copy_redir, 0));
}

char	*iter_process_cmd(t_list *process_list)
{
	return(listiter_cmd(process_list, (void *)&copy_process, 1));
}

char	*iter_cmd(t_node_p process_tree)
{
	char	*s;
	char	*tmp;

	s = NULL;
	if (process_tree->type IS PROCESS)
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
//	PUT2("\n----command----\n");
//	PUT2(s);
//	PUT2("\n--------\n");
	return (s);
}
