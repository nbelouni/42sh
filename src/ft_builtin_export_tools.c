/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:19:12 by dogokar           #+#    #+#             */
/*   Updated: 2017/03/15 18:19:59 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**		extrais l'element et l'insert dans une autre liste
*/

void		move_to_env(t_elem *lst, t_lst *env, t_lst *type_env)
{
	ft_extract_elem(&lst, type_env);
	ft_insert_elem(lst, env);
}

/*
**  ajoute un element sans les messages d'erreurs
*/

int			ft_add_elemo(t_lst *lst, char *s)
{
	t_elem	*elem;

	elem = NULL;
	if (s && s[0])
	{
		if ((elem = ft_init_elem()) == NULL)
			return (ERR_EXIT);
		elem->name = ft_strdup(s);
		ft_insert_elem(elem, lst);
		return (0);
	}
	return (-1);
}

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
