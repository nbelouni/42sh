/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:08:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:01 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	opt -> {fin options, 'L', 'P'}
*/

/*
**	ft_cd est l'etape finale du builtin cd, permettant de changer de dossier
**	et actualisant/creant le PWD et l'OLDPWD
*/

static int	ft_cd(t_lst *env, int *opt, char *s)
{
	int		ret;
	char	*owd;
	char	*cwd;

	ret = 0;
	if (ft_is_valid_dir(s) == -1)
		return (-1);
	owd = getcwd(NULL, PATH_MAX);
	chdir(s);
	cwd = (opt && opt[2]) ? getcwd(NULL, PATH_MAX) : concat_path(s);
	ret = ft_pwd_swap(env, owd, cwd);
	(owd) ? ft_strdel(&owd) : 0;
	(cwd) ? ft_strdel(&cwd) : 0;
	return (ret);
}

/*
**	ft_concat_path est une etape intermediaire permettant de remplacer
**	s1 par s2 et de tester la validité du dossier. Elle est appelé si cd
**	possede 2 arguments en dehors des options.
*/

char		*ft_concat_path(char *res, char *s1, char *s2, size_t len)
{
	char		*b1;
	char		*b2;
	size_t		i;

	i = ft_strlen(res);
	if ((b1 = ft_strsub(res, 0, (i - len))) == NULL)
		return (NULL);
	if ((b2 = ft_strsub(res, (i - len + ft_strlen(s1)), PATH_MAX)) == NULL)
	{
		ft_strdel(&b1);
		return (NULL);
	}
	ft_memset(res, 0, PATH_MAX);
	res = ft_multi_concat(res, b1, s2, b2);
	ft_multi_free(b1, b2, NULL, NULL);
	if (ft_is_valid_dir(res) == -1)
	{
		ft_strdel(&res);
	}
	return (res);
}

/*
**	check s'il y a des arguments pour creer le path, s'il n'y en a pas,
**	il prend par default la valeur de la variable HOME, qui, si elle n'est
**	pas set, sera NULL.
*/

static char	*ft_builtin_cd_norm(t_lst *env, char **args)
{
	char		*path;
	t_elem		*e;

	path = NULL;
	if (args != NULL && args[0] != NULL)
	{
		if ((path = ft_create_path(env, args[0], args[1])) == NULL)
			return (NULL);
	}
	else
	{
		if ((e = ft_find_elem("HOME", env)) == NULL)
			ft_print_error("cd", ERR_HOME_NOT_SET, ERR_NEW_CMD);
		if (e != NULL && e->value != NULL)
		{
			if ((path = ft_create_path(env, e->value, NULL)) == NULL)
				return (NULL);
		}
	}
	return (path);
}

/*
**	builtin qui permet de changer de directory, il peut recevoir, hors options,
**	soit aucun arguments, soit jusqu'a 2 arguments. Il renverra une erreur si
**	plus d'arguments sont trouvés.
*/

int			ft_builtin_cd(t_core *core, char **args)
{
	struct stat	st;
	int			*opt;
	int			i;
	char		*s;

	if (!(opt = ft_opt_parse(CD_OPT, args, 1, 0)))
		return (ERR_EXIT);
	else if (opt[0] == -1)
		return (ft_free_and_return(ERR_NEW_CMD, opt, NULL, NULL));
	if (args != NULL && args[opt[0]] != NULL && ft_tablen(&(args[opt[0]])) > 2)
	{
		(opt != NULL) ? free(opt) : 0;
		return (ft_print_error("cd", ERR_TOO_MANY_ARGS, ERR_NEW_CMD));
	}
	i = -1;
	if ((s = ft_builtin_cd_norm(core->env, &(args[opt[0]]))) != NULL)
	{
		i = ((lstat(s, &st)) != -1) ? ft_cd(core->env, opt, s) :\
			ft_print_error(s, ERR_NO_FILE, ERR_NEW_CMD);
		ft_strdel(&s);
	}
	(opt) ? free(opt) : 0;
	return (i);
}
