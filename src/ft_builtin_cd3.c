/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 20:47:27 by maissa-b          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:01 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		supp_files(char **files)
{
	int		i;

	i = -1;
	while (files[++i])
	{
		if (!ft_strcmp(files[i], "."))
		{
			ft_strdel(&(files[i]));
			files[i] = ft_strdup("");
		}
		if (!ft_strcmp(files[i], ".."))
		{
			ft_strdel(&(files[i]));
			files[i] = ft_strdup("");
			if (i > 0)
			{
				ft_strdel(&(files[i - 1]));
				files[i - 1] = ft_strdup("");
			}
		}
	}
}

int			files_len(char **files)
{
	int		i;
	int		new_len;

	new_len = 1;
	i = -1;
	while (files[++i])
	{
		new_len += ft_strlen(files[i]);
		if (files[i][0])
			new_len += 1;
	}
	return (new_len);
}

char		*concat_path(char *s)
{
	char	**files;
	char	*new;
	int		i;

	if (!(files = ft_strsplit(s, '/')))
		return (NULL);
	supp_files(files);
	if (!(new = ft_strnew(files_len(files))))
		return (NULL);
	i = -1;
	ft_strcat(new, "/");
	while (files[++i])
	{
		if (files[i][0] != '\0')
		{
			ft_strcat(new, files[i]);
			ft_strcat(new, "/");
		}
	}
	ft_tabdel(files);
	return (new);
}
