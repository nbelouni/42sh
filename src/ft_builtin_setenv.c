/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:22:07 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/30 21:23:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_setenv est une fonction qui va attribué la valeur de var a name et
**	la valeur de word a value de l'element tmp, et finir par ajouter ce maillon
**	a la liste env. Word peut etre NULL, pas var.
*/

int			ft_setenv(t_lst *env, char *var, char *word)
{
	t_elem	*tmp;

	tmp = NULL;
	if ((tmp = ft_find_elem(var, env)) == NULL)
	{
		if ((tmp = ft_init_elem()) == NULL)
			return (ERR_EXIT);
		ft_insert_elem(tmp, env);
		if ((tmp->name = ft_strdup(var)) == NULL)
			return (ERR_EXIT);
	}
	else
	{
		if (tmp->value != NULL && tmp->value[0] != '\0')
			ft_strdel(&tmp->value);
	}
	if (word != NULL && word[0] != '\0')
	{
		if ((tmp->value = ft_strdup(word)) == NULL)
			return (ERR_EXIT);
	}
	return (0);
}

/*
**	ft_exec_setenv verifie qu'il n'y a pas de caractere '=' dans la premiere
**	chaine d'args (qui sera le futur elem->name), qu'il y a bien un caractere
**	non digital en premiere position de cette chaine, puis finit par verifier
**	le nombre de chaines dans args, renvoi une erreur s'il y en a plus de 2.
**	Si aucune erreur n'est trouvé, ft_setenv est appelé.
*/

static int	ft_exec_setenv(t_lst *env, char **args)
{
	if (ft_strchr(args[0], '=') != NULL)
	{
		return (ft_print_error("cd", ERR_VAR_NO_ALPHA, ERR_NEW_CMD));
	}
	else if (ft_isalpha(args[0][0]) == 0)
	{
		return (ft_print_error("cd", ERR_VAR_BEG_NO_ALPHA, ERR_NEW_CMD));
	}
	else
	{
		if (args[1] != NULL && args[2] != NULL)
		{
			return (ft_print_error("cd", ERR_TOO_MANY_ARGS, ERR_NEW_CMD));
		}
		return (ft_setenv(env, args[0], args[1]));
	}
}

/*
**	la fonction ft_builtin_setenv s'occupe du builtin setenv,
**	elle ne gere pas les erreurs, c'est ft_exec_setenv qui s'en charge,
**	s'il n'y a pas d'arguments, le builtin setenv affiche la liste env.
*/

int			ft_builtin_setenv(t_core *core, char **args)
{
	if (args != NULL && args[0] != NULL)
		return (ft_exec_setenv(g_core->env, args));
	if (g_core->env != NULL && g_core->env->head != NULL)
		ft_print_lst(g_core->env);
	return (0);
}
