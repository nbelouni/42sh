/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:13:34 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:14:32 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_sub_reloaded(t_str *s_str, char **line, int const fd)
{
	char			*tmp;

	tmp = NULL;
	if (s_str->fd != fd)
	{
		s_str->i = 0;
		s_str->j = 0;
		s_str->fd = fd;
	}
	while (s_str->s[s_str->i])
	{
		if (s_str->s[s_str->i] == '\n')
		{
			tmp = ft_strsub(s_str->s, s_str->j, (s_str->i - s_str->j));
			*line = ft_free_and_dup(*line, tmp);
			ft_strdel(&tmp);
			s_str->i++;
			s_str->j = s_str->i;
			return (1);
		}
		s_str->i++;
	}
	return (0);
}

static int	exec_get_next_line(t_str *s_str, char **s, int const fd, char *buf)
{
	char			*tmp;

	tmp = NULL;
	while ((s_str->read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[s_str->read] = '\0';
		tmp = s_str->s;
		s_str->s = ft_strjoin(tmp, buf);
		if (tmp)
			ft_strdel(&tmp);
	}
	if (s_str->read == -1)
		return (-1);
	if (ft_sub_reloaded(s_str, s, fd) == 1)
		return (1);
	tmp = ft_strsub(s_str->s, s_str->j, (s_str->i - s_str->j));
	*s = ft_free_and_dup(*s, tmp);
	ft_strdel(&tmp);
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static t_str	s_str;

	if (BUFF_SIZE <= 0 || !line || fd < 0)
		return (-1);
	if (!s_str.s)
		s_str.fd = fd;
	if (!s_str.s || s_str.fd != fd)
	{
		if ((s_str.s = (char *)malloc(sizeof(s_str.s))))
			s_str.s[0] = '\0';
	}
	ret = exec_get_next_line(&s_str, line, fd, buf);
	return (ret);
}
