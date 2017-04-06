/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_for_job.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:03:43 by alallema          #+#    #+#             */
/*   Updated: 2017/04/06 16:58:20 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"

static t_redir		(g_tab_redir[7]) = {
	[0] = { "< ", O_RDONLY},
	[1] = { "> ", O_WRONLY | O_CREAT | O_TRUNC},
	[2] = { "<< ", 0},
	[3] = { ">> ", O_WRONLY | O_CREAT | O_APPEND},
	[4] = { "<> ", O_RDWR | O_CREAT},
	[5] = { "<&", O_RDWR},
	[6] = { ">&", O_RDWR | O_TRUNC},
};

char		*ft_fix_join(char *s, char *buf)
{
	char			*tmp;

	tmp = s;
	s = ft_strjoin(tmp, buf);
	free(tmp);
	free(buf);
	return (s);
}

char		*copy_redir(t_io *io)
{
	char	*s;
	char	*tmp;
	int		i;

	i = 0;
	s = NULL;
	tmp = NULL;
	if (io->str && io->mode)
	{
		while (i < 7)
		{
			if (io->mode == g_tab_redir[i].mode)
			{
				if (i == 5 || i == 6)
					tmp = ft_itoa(io->dup_target);
				s = ft_strjoin(g_tab_redir[i].redir, io->str);
			}
			i++;
		}
	}
	if (tmp)
		s = ft_fix_join(tmp, s);
	s = ft_fix_join(s, ft_strdup(" "));
	return (s);
}

char		*copy_process(t_process_p process)
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
