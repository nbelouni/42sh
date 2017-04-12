/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:08:28 by alallema          #+#    #+#             */
/*   Updated: 2017/04/12 04:06:55 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** decoupe la path pour effectue l'execution du binaire dans chaque dossier
*/

static char		*ft_cut_path(char **s, char *av)
{
	char		*s1;
	char		*s2;
	int			i;

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
** fonction d'execution des commandes via execve
** lstat verifie l'authorisation d'execution
*/

void			not_binary(char *s, char *s2, char **av, char **envp)
{
	struct stat	st;

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
			exit(127);
		}
		else
			ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putendl_fd(av[0], 2);
		free(s);
		s = NULL;
		exit(1);
	}
}

/*
** recuperer l'env pour execve
** remplace le path pour l'envoie a execve
*/
int			investigate(char *func);
void			ft_exec(char **av)
{
	char		*s;
	char		*s2;
	char		**envp;
	t_elem		*tmp;

	investigate((char *)__func__);
	close_termios();
	envp = ft_env_to_tab(core->env);
	if (!(tmp = ft_find_elem("PATH", core->env)))
		s = ft_strdup("");
	else
		s = ft_strdup(tmp->value);
	while (s)
	{
		s2 = ft_cut_path(&s, av[0]);
		not_binary(s, s2, av, envp);
	}
}

/*
** edit_cmd remplace la commande avec la completion
** sert a retourner si la cmd c'est un builtin
*/

int				ft_check_exec(char ***cmd)
{
	int			ret;

	ret = TRUE;
	if (edit_cmd(cmd, core) == ERR_EXIT)
		return (ERR_EXIT);
	if ((ret = parse_builtins(core, *cmd[0], *cmd + 1)) != 0)
		ft_exec(*cmd);
	return (ret);
}
