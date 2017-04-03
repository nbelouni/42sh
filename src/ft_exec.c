/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:08:28 by alallema          #+#    #+#             */
/*   Updated: 2017/04/03 16:44:08 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char		*ft_cut_path(char **s, char *av)
{
	char	*s1;
	char	*s2;
	int		i;

	i = 0;
	s1 = *s;
	while (s1[i] != ':')
		i++;
	s2 = ft_memalloc(sizeof(char *) * (i + 2 + ft_strlen(av)));
	s2 = ft_strncpy(s2, s1, i);
	ft_strncpy(&s2[i], "/", 1);
	ft_strncpy(&s2[i + 1], av, ft_strlen(av));
	if (s1[i] == ':')
		i++;
	s1 = ft_strdup(&s1[i]);
	free(*s);
	*s = s1;
	return (s2);
}

/*
 **execute la cmd si est un builtin
 */
/*
int			ft_exec_built(char **args)
{
	int		ret;

	ret = TRUE;
	if (args != NULL && args[0] != NULL)
	{
		if ((ret = ft_strcmp(args[0], "exit")) == FALSE)
			ft_builtin_exit(core, args[0], args + 1);
		else if ((ret = ft_strcmp(args[0], "env")) == FALSE)
			ft_builtin_env(core->env, &args[1]);
		else if ((ret = ft_strcmp(args[0], "setenv")) == FALSE)
			ft_builtin_setenv(core->env, args[0], args + 1);
		else if ((ret = ft_strcmp(args[0], "unsetenv")) == FALSE)
			ft_builtin_unsetenv(core->env, args[0], &args[1]);
		else if ((ret = ft_strcmp(args[0], "echo")) == FALSE)
			ft_builtin_echo(core->env, args[0], args + 1);
		else if ((ret = ft_strcmp(args[0], "cd")) == FALSE)
			ft_builtin_cd(core->env, args[0], args + 1);
		else if ((ret = ft_strcmp(args[0], "fg")) == FALSE)
			ft_builtin_fg(core, args + 1);
		return (ret);
	}
	return (FALSE);
}
*/

/*
** fonction d'execution des commandes via execve
*/
void			ft_exec(char **av)
{
	struct stat	st;
	char		*s;
	char		*s2;
	char		**envp;
	t_elem		*tmp;

	close_termios();
	envp = ft_env_to_tab(core->env);
	if (!(tmp = ft_find_elem("PATH", core->env)))
		s = ft_strdup("");
	else
		s = ft_strdup(tmp->value);
	while (s)
	{
		s2 = ft_cut_path(&s, av[0]);
		if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR)
			execve(av[0], av, envp);
		if (lstat(s2, &st) == 0 && st.st_mode & S_IXUSR)
			execve(s2, av, envp);
		if (!ft_strchr(s, ':'))
		{
			if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR)
				ft_putstr_fd("42sh: exec format error: ", 2);
			else if (lstat(av[0], &st) == 0)
				ft_putstr_fd("42sh: permission denied: ", 2);
			else if (!ft_strchr(s2, ':'))
			{
				ft_putstr_fd("42sh: command not found: ", 2);
				ft_putendl_fd(av[0], 2);
				exit (127);
			}
			else
				ft_putstr_fd("42sh: no such file or directory: ", 2);
			ft_putendl_fd(av[0], 2);
			free(s);
			s = NULL;
			exit(1);
		}
	}
}

/*
**sert a retourner si la cmd est un builtin
*/

int		parse_builtins(t_core *core, char *cmd, char **cmd_args);

int		ft_check_exec(char **cmd)
{
	int		ret;

	ret = TRUE;
//	if ((ret = ft_exec_built(cmd)) != 0)
	if ((ret = parse_builtins(core, cmd[0], cmd + 1)) != 0)
		ft_exec(cmd);
	return (ret);
}
