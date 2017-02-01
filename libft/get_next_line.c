/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <nbelouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 02:10:38 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/01 17:49:39 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*add_buff(char **dst, char *src)
{
	char		*tmp;
	int			len_src;
	int			len_dst;

	len_src = ft_strlen(src);
	if (!*dst)
	{
		tmp = (char *)malloc(sizeof(char) * (len_src + 1));
		if (!tmp)
			return (NULL);
		ft_strcpy(tmp, src);
	}
	else
	{
		len_dst = ft_strlen(*dst);
		tmp = (char *)malloc(sizeof(char) * (len_dst + len_src + 1));
		if (!tmp)
			return (NULL);
		ft_strcpy(tmp, *dst);
		ft_strcpy(tmp + len_dst, src);
		free(*dst);
		*dst = NULL;
	}
	return (tmp);
}

static int		parse_line(char **line, char **rst)
{
	char		*tmp1;
	char		*tmp2;

	if (!*rst)
		return (0);
	tmp1 = ft_strchr(*rst, '\n');
	if (tmp1)
	{
		tmp1[0] = '\0';
		*line = ft_strdup(*rst);
		tmp2 = tmp1 + 1;
		free(*rst);
		*rst = NULL;
		*rst = ft_strdup(tmp2);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*stat;
	char		*tmp;
	int			ret;

	if (fd < 0)
		return (0);
	if (parse_line(line, &stat))
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		stat = add_buff(&stat, buf);
		tmp = ft_strchr(stat, '\n');
		if (tmp)
			if (parse_line(line, &stat))
				return (1);
	}
	if (ret < 0)
		return (-1);
	return (0);
}
