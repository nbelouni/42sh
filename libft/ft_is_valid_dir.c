/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 20:17:36 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/05 14:03:46 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_valid_dir(const char *dirname)
{
	DIR			*dir;
	struct stat st;

	lstat(dirname, &st);
	if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode))
	{
		if ((dir = opendir(dirname)))
		{
			closedir(dir);
			return (0);
		}
		return (ft_print_error("cd", ERR_NO_ACCESS, ERR_NEW_CMD));
	}
	else
	{
		return (ft_print_error("cd", ERR_NO_FILE, ERR_NEW_CMD));
	}
}
