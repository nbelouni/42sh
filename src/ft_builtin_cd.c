/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:21:51 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 20:01:43 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int	ft_cd(t_lst *env, int *opt, char *path, mode_t m)
{
	char	*buf;
	char	*b2;
	char	*owd;

	buf = ft_strnew(PATH_MAX);
	if (S_ISLNK(m) && opt && opt[1])
		readlink(path, buf, PATH_MAX);
	else
		ft_strcpy(buf, path);
	if (ft_is_valid_dir(buf) == 0)
	{
		owd = getcwd(NULL, PATH_MAX);
		chdir(buf);
		b2 = getcwd(NULL, PATH_MAX);
		if (S_ISLNK(m) && opt && opt[0] && opt[1])
		{
			ft_memset(ft_strlchr(b2, '/'), 0, ft_strlen(ft_strlchr(b2, '/')));
			b2 = ft_free_and_join(b2, ft_strlchr(path, '/'));
		}
		if ((ft_pwd_swap(env, owd, b2)) != 0)
			return (ERR_EXIT);
		ft_multi_free(owd, buf, b2, NULL);
		return (0);
	}
	return (-1);
}

static char	*ft_switch_path(char *dir1, char *dir2)
{
	char		*path;
	char		*buf1;
	char		*buf2;
	char		*ptr;
	size_t		i;

	path = ft_strnew(PATH_MAX);
	getcwd(path, PATH_MAX);
	if ((ptr = ft_strstr(path, dir1)) == NULL)
		ft_print_error(dir1, ERR_STR_NOT_IN_PWD, ERR_NEW_CMD);
	else
	{
		i = ft_strlen(path);
		buf1 = ft_strsub(path, 0, i - ft_strlen(ptr));
		buf2 = ft_strsub(path, i - ft_strlen(ptr) + ft_strlen(dir1), PATH_MAX);
		ft_memset(path, 0, PATH_MAX);
		ft_strcpy(path, buf1);
		path = ft_strcat(path, dir2);
		path = ft_strcat(path, buf2);
		if (ft_is_valid_dir(path) == -1)
			ft_strdel(&path);
		ft_multi_free(buf1, buf2, NULL, NULL);
	}
	return (path);
}

static char	*ft_create_path(t_lst *env, char *arg1, char *arg2)
{
	char		*f_path;
	char		*cwd;
	t_elem		*elem;

	if (arg1 && (!arg2 || !arg2[0]))
	{
		if (ft_strcmp(arg1, "-") == 0)
		{
			if ((elem = ft_find_elem("OLDPWD", env)) == NULL)
				ft_print_error("cd -", ERR_OLDPWD_NOT_SET, ERR_NEW_CMD);
			f_path = (elem && elem->value) ? ft_strdup(elem->value) : NULL;
		}
		else if (arg1[0] != '/')
		{
			cwd = getcwd(NULL, PATH_MAX);
			f_path = ft_strnew(PATH_MAX);
			f_path = ft_multi_concat(f_path, cwd, "/", arg1);
			ft_strdel(&cwd);
		}
		else
			f_path = ft_strdup(arg1);
	}
	else
		f_path = ft_switch_path(arg1, arg2);
	return (f_path);
}

static char	*ft_builtin_cd_norm(t_lst *env, int *opt, char **args)
{
	char		*path;
	t_elem		*e;

	path = NULL;
	if ((e = ft_find_elem("HOME", env)) == NULL)
		ft_print_error("cd", ERR_HOME_NOT_SET, ERR_NEW_CMD);
	else if (args && args[opt[0]] && args[opt[0]][0])
		path = ft_create_path(env, args[opt[0]], args[opt[0] + 1]);
	else
		path = (e && e->value) ? ft_create_path(env, e->value, NULL) : NULL;
	return (path);
}

int			ft_builtin_cd(t_lst *env, char *cmd, char **args)
{
	struct stat	st;
	int			*opt;
	int			i;
	char		*path;

	opt = NULL;
	if ((opt = ft_opt_parse(opt, CD_OPT, args, 1)) == (int *)-1)
		return (-1);
	if (args && args[opt[0]] && ft_tablen(&(args[opt[0]])) > 2)
	{
		(opt && opt[0]) ? free(opt) : 0;
		return (ft_print_error(cmd, ERR_TOO_MANY_ARGS, ERR_NEW_CMD));
	}
	i = -1;
	if ((path = ft_builtin_cd_norm(env, opt, args)) != NULL)
	{
		i = ((lstat(path, &st)) != -1) ? ft_cd(env, opt, path, st.st_mode) : \
			ft_print_error(path, ERR_NO_FILE, ERR_NEW_CMD);
		ft_strdel(&path);
	}
	(opt) ? free(opt) : 0;
	return (i);
}
