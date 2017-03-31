/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:33:52 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/20 14:33:54 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_join(char *tmp, char *buf)
{
	int			i;
	int			len;
	char		*s;

	i = 0;
	if (tmp == NULL && buf == NULL)
		return (NULL);
	len = ft_strlen(tmp) + ft_strlen(buf);
	if (!(s = ft_memalloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (tmp && tmp[i])
	{
		s[i] = tmp[i];
		i++;
	}
	free(tmp);
	tmp = NULL;
	while (*buf && i < len)
	{
		s[i] = *buf;
		i++;
		buf++;
	}
	s[i] = '\0';
	return (s);
}

static void		ft_cpytmp(char *tmp, char **line)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(tmp);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
	{
		*line = ft_memalloc(sizeof(char *) * ft_strlen(*line) + i + 1);
		*line = ft_strncpy(*line, (const char *)tmp, (size_t)i);
	}
	if (len - i != 0)
		tmp = ft_strncpy(tmp, (const char *)&tmp[i + 1], (size_t)len - i);
	else
		free(tmp);
	tmp = NULL;
}

int				get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*tmp;
	int			ret;

	ret = read(fd, &buf, BUFF_SIZE);
	buf[ret] = '\0';
	if (fd < 0 || ret < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (ret == 0 && ft_strcmp(tmp, "") == 0)
		return (0);
	tmp = ft_join(tmp, buf);
	if (!ft_strchr(tmp, '\n'))
		get_next_line(fd, line);
	else
		ft_cpytmp(tmp, line);
	return (1);
}
