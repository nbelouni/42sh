/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:24:17 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/29 14:46:46 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	Ft_parse_env est une fonction qui va parcourir args afin d'y trouver
**	le format var=value, si il ne trouve pas var=value, il retourne ret qui est
**	l'index dans les args où l'export de type var=value se termine, sinon
**	il export la chaine contenu dans args.
*/

static int		ft_parse_env(t_lst *lst, char **args)
{
	int		ret;
	int		ret2;

	ret = 0;
	ret2 = 0;
	if (args != NULL && args[ret] != NULL)
	{
		while (args[ret] != NULL)
		{
			if (ft_strchr(args[ret], '=') == NULL)
			{
				return (ret);
			}
			else
			{
				if ((ret2 = ft_export(lst, args[ret])) != 0)
					return (ret2);
			}
			++ret;
		}
		++ret;
	}
	return (ret);
}

/*
**	Ft_getlst_env permet simplement d'initialisé et/ou de de copier la liste
**	dans dup, puis de la retourner, selon si env est remplis ou non.
*/

static t_lst	*ft_getlst_env(t_lst *env, int *opt)
{
	t_lst	*dup;

	dup = NULL;
	if ((dup = ft_init_list()) == NULL)
	{
		return (NULL);
	}
	if (env != NULL && opt[1] != 1)
	{
		if ((dup = ft_lstcpy(dup, env)) == NULL)
		{
			ft_del_list(dup);
		}
	}
	return (dup);
}

/*
**	ft_exec_env est appellée par ft_builtin_env afin de gerer ce dernier,
**	il va verifier que les erreurs d'options ne sont pas présents, ainsi
**	que verifier si l'allocation/duplication de la liste s'est bien déroulé,
**	selon si l'option i est set ou non, auquel cas il retourne une erreur.
**	Si tout s'est bien passé, ft_parse_env est appelé avec les arguments
**	partant de la fin des options.
*/

static int		ft_exec_env(t_lst *env, char **args)
{
	int		ret;
	int		*opt;
	t_lst	*dup;

	if ((opt = ft_opt_parse(ENV_OPT, args, 0)) == NULL)
		return (ERR_EXIT);
	if (opt[0] == -1)
		return (ft_free_and_return(ERR_NEW_CMD, opt, NULL, NULL));
	if ((dup = ft_getlst_env(env, opt)) == NULL)
		return (ft_free_and_return(ERR_EXIT, opt, NULL, NULL));
	if (args[opt[0]] != NULL && args[opt[0]][0] != '\0')
	{
		ret = ft_parse_env(dup, &(args[opt[0]]));
		if (ret < 0)
			return (ft_free_and_return(ret, opt, NULL, NULL));
		if (ret > (int)ft_tablen(args) || !args[ret] || !args[ret][0])
			(dup != NULL) ? ft_print_lst(dup) : 0;
		else
			ft_putendl("bin execution");
	}
	else
		(dup != NULL) ? ft_print_lst(dup) : 0;
	free(opt);
	(dup != NULL) ? ft_del_list(dup) : 0;
	return (0);
}

/*
**	la fonction ft_builtin_env permet de gerer le builtin selon les arguments,
**	s'il n'y en a pas, la liste pointée par env est affichée,
**	sinon, ft_exec_env est appellé pour gerer les cas specifiques au builtin.
*/

int				ft_builtin_env(t_core *core, char **args)
{
	int		ret;

	ret = 0;
	if (args == NULL || *args == NULL)
	{
		if (core->env != NULL && core->env->head != NULL)
		{
			ft_print_lst(core->env);
		}
	}
	else
	{
		ret = ft_exec_env(core->env, args);
	}
	return (ret);
}
