/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:08:28 by alallema          #+#    #+#             */
/*   Updated: 2017/04/30 21:02:40 by nbelouni         ###   ########.fr       */
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
	char		*tmp;
	int			i;

	i = 0;
	s1 = *s;
	while (s1[i] && s1[i] != ':')
		i++;
	s2 = ft_memalloc(sizeof(char) * (i + 2 + ft_strlen(av)));
	ft_strncpy(s2, s1, i);
	ft_strncpy(s2 + i, "/", 1);
	ft_strncpy(s2 + i + 1, av, ft_strlen(av));
	if (s1[i] && s1[i] == ':')
		i++;
	tmp = ft_strdup(s1 + i);
	s1 = NULL;
	ft_strdel(s);
	*s = tmp;
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
	if (!s)
	{
		if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR)
			ft_putstr_fd("21sh: exec format error: ", 2);
		else if (lstat(av[0], &st) == 0)
			ft_putstr_fd("21sh: permission denied: ", 2);
		else
			ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putendl_fd(av[0], 2);
		free(s);
		free(s2);
		s = NULL;
		exit(1);
	}
}

/*
** recuperer l'env pour execve
** remplace le path pour l'envoie a execve
*/
//int			investigate(char *func);
void			ft_exec(char **av)
{
	char		*s;
	char		*s2;
	char		**envp;
	t_elem		*tmp;

	close_termios();
	envp = ft_env_to_tab(g_core->env);
	if (!(tmp = ft_find_elem("PATH", g_core->env)) || !tmp->value)
		s = ft_strdup("");
	else
		s = ft_strdup(tmp->value);
	while (true)
	{
		s2 = ft_cut_path(&s, av[0]);
		not_binary(s, s2, av, envp);
		if (ft_strcmp(s, "") == 0)
			break ;
	}
	ft_putstr_fd("21sh: command not found: ", 2);
	free(s);
	free(s2);
	free(envp);
	ft_putendl_fd(av[0], 2);
	exit(127);
}

/*
** edit_cmd remplace la commande avec la completion
** sert a retourner si la cmd c'est un builtin
*/

int				ft_check_exec(char ***cmd)
{
	int			ret;

	ret = TRUE;
	if (edit_cmd(cmd, g_core) == ERR_EXIT)
		return (ERR_EXIT);
	if ((ret = parse_builtins(g_core, *cmd[0], *cmd + 1)) == 1)
		ft_exec(*cmd);
	return (ret);
}
