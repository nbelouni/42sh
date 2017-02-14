/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 20:17:36 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 19:00:56 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_valid_dir(const char *dirname)
{
	DIR			*dir;
	struct stat st;

	dir = NULL;
	ft_memset(&st, 0, sizeof(struct stat));
	lstat(dirname, &st);
	if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode))
	{
		if ((dir = opendir(dirname)))
		{
			closedir(dir);
			return (0);
		}
		return (ft_print_error((char *)dirname, ERR_NO_ACCESS, ERR_NEW_CMD));
	}
	else
	{
		return (ft_print_error((char *)dirname, ERR_NO_FILE, ERR_NEW_CMD));
	}
}
