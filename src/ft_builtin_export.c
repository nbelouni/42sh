/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:08:02 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/04 16:14:23 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**		prend un maillon de varaible contenue dans n'importe quel liste et
**		l'insert dans la liste de variable d'environnement
*/

int			insert_to_env(t_elem *node, char *arg, t_lst *env, t_lst *type_env)
{
	char	*val;
	int		ret;
	char 	*i;

	ret = 0;
	val = NULL;
	i = ft_strchr(arg, '=');
	if ((ft_strlen(node->name)  + 1) < ft_strlen(arg) && i)
	{
		if ((val = ft_strsub(arg, ft_strlen(node->name) + 1,
					(ft_strlen(arg) - ft_strlen(node->name) + 1))) == NULL)
				return (ft_free_and_return(ERR_EXIT, node->name, NULL, NULL));
		ft_strdel(&(node->value));
		node->value = ft_strdup(val);
		ft_strdel(&val);
	}
	else if (node->value && i)
		ft_strdel(&node->value);
	if (type_env)
		move_to_env(node, env, type_env);
	return (0);
}

/*
**			va chercher la variable dans une liste
*/

t_elem		*search_var(char *arg, t_lst *type_env)
{
	t_elem	*tmp;
	char	*name;

	tmp = NULL;
	if (ft_strchr(arg, '='))
		name = ft_strsub(arg, 0, ft_get_index_of(arg, '='));
	else
		name = ft_strdup(arg);
	if (name == NULL || name[0] == '\0' || name[0] == '=')
		return (NULL);
	tmp = ft_find_elem(name, type_env);
	ft_strdel(&name);
	return (tmp);
}

/*
**		insert_to_exp va verifier si la variable comporte un '='
**		si c'est le cas il va l'inserer dans l'env si non dans la liste d'exp
*/

int			insert_to_exp(char *argv, t_core *m_env)
{
	char	*tmp;
	int		result;

	tmp = NULL;
	result = 0;
	if (!ft_strchr(argv, '='))
	{
		if (!m_env->exp)
			m_env->exp = ft_init_list();
		return (ft_add_elemo(m_env->exp, argv));
	}
	else
		return (ft_export(m_env->env, argv));
	return (0);
}

/*
**	va chercher dans les diffrents listes de varaiable, si la variable
**	existe il va l'inserer dans l'env
**	si non il va la cree avec insert_to_exp
*/

static int	multi_var_check(char *argv, t_core *m_env)
{
	t_elem	*tmp;

	tmp = NULL;
	if (argv[0] == '=' || ft_isalpha(argv[0]) == 0)
		return (ft_print_error(&argv[0], ERR_VAR_BEG_NO_ALPHA, -1));
	if ((tmp = search_var(argv, m_env->exp)))
		return (insert_to_env(tmp, argv, m_env->env, m_env->exp));
	else if ((tmp = search_var(argv, m_env->set)))
		return (insert_to_env(tmp, argv, m_env->env, m_env->set));
	else if ((tmp = search_var(argv, m_env->env)))
		return (insert_to_env(tmp, argv, m_env->env, NULL));
	else if (!tmp && argv)
		return (insert_to_exp(argv, m_env));
	return (-1);
}

/*
**   gestion des erreurs et debut de fonction
*/

int			ft_builtin_export(t_core *m_env, char **argv)
{
	int		*opt;
	int		i;
	int		result;

	if (!(opt = ft_opt_parse(EXPORT_OPT, argv, 0, 0)))
		return (ERR_EXIT);
	if (opt[0] == -1)
	{
		free(opt);
		return (ERR_NEW_CMD);
	}
	i = opt[0];
	result = 0;
	if (argv[i] == NULL)
		ft_print_export(m_env);
	while (argv[i] != NULL)
	{
		if (multi_var_check(argv[i], m_env) == -1)
			result = ERR_NEW_CMD;
		++i;
	}
	free(opt);
	return (result);
}
