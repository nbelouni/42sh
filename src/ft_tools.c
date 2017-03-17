/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:18:39 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/15 19:06:57 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_export est une fonction permettant d'exporter dans une liste lst
**	la chaine de caracteres arg, contenant par default un caractere '=',
**	divisé sous forme name=value, elem->name contenant name et elem->value
**	contenant value
*/

int			ft_export(t_lst *lst, char *arg)
{
	char	*name;
	char	*val;
	int		ret;

	if ((name = ft_strsub(arg, 0, ft_get_index_of(arg, '='))) == NULL)
		return (ERR_EXIT);
	ret = 0;
	if (name == NULL || name[0] == '\0' || name[0] == '=')
		return (ft_print_error("42sh", ERR_ARG_INVALID, ERR_NEW_CMD));
	val = NULL;
	if ((ft_strlen(name) + 1) < ft_strlen(arg))
	{
		if ((val = ft_strsub(arg, ft_strlen(name) + 1, \
				(ft_strlen(arg) - ft_strlen(name) + 1))) == NULL)
			return (ft_free_and_return(ERR_EXIT, name, NULL, NULL));
	}
	ret = ft_setenv(lst, name, val);
	(val != NULL) ? ft_multi_free(val, name, NULL, NULL) : ft_strdel(&name);
	return (ret);
}
