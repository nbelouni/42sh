/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:08:06 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:01 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_core	*g_core;

int				ft_exec_env_binary(t_lst *env, char **args)
{
	t_lst	*env_tmp;

	env_tmp = NULL;
	if (args && args[0])
	{
		env_tmp = g_core->env;
		g_core->env = env;
		ft_exec(args);
		g_core->env = env_tmp;
	}
	return (0);
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
	if (env != NULL && opt != NULL && opt[1] != 1)
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

static int		ft_exec_env(t_lst *env, int *opt, char **args)
{
	t_lst	*dup;
	int		ret;
	int		i;

	dup = NULL;
	if ((dup = ft_getlst_env(env, opt)) == NULL)
		return (ERR_EXIT);
	i = -1;
	ret = 0;
	while (args[++i])
	{
		if (!(ft_strchr(args[i], '=')) || (ret = ft_export(dup, args[i])) < 0)
			break ;
	}
	if (ret >= 0)
	{
		(args[i]) ? ft_exec_env_binary(dup, &(args[i])) : ft_print_lst(dup);
	}
	(dup) ? ft_del_list(dup) : 0;
	return (ret);
}

int				ft_builtin_env(t_core *core, char **args)
{
	int		*opt;
	int		ret;

	ret = 0;
	opt = NULL;
	if (args == NULL || args[0] == NULL)
	{
		if (core->env && core->env->head)
			ft_print_lst(core->env);
		return (0);
	}
	if ((opt = ft_opt_parse(ENV_OPT, args, 0, 0)) == NULL)
		return (ERR_EXIT);
	if (opt[0] < 0)
		ret = opt[0];
	else
	{
		if (args[opt[0]] != NULL)
			ret = ft_exec_env(core->env, opt, &(args[opt[0]]));
	}
	free(opt);
	return (ret);
}
