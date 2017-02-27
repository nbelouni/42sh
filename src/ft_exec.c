/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:08:28 by alallema          #+#    #+#             */
/*   Updated: 2017/02/27 23:46:30 by alallema         ###   ########.fr       */
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
	*s = &s1[i];
	return (s2);
}

/*
** fonction d'execution des commandes via execve
** s-> path a changer avec la hastable
*/

void			ft_exec(t_word *string, t_lst *env)
{
	struct stat	st;
	char		*s;
	char		*s2;
	char		**av;
	char		**envp;

	av = ft_memalloc(sizeof(char *) * 2);
	av[0] = string->s;
	av[1] = NULL;
	envp = ft_env_to_tab(env);
	s = "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/usr/local/munki:/Users/alallema/bin:/Users/alallema/.rvm/bin";
	while (1)
	{
		s2 = ft_cut_path(&s, av[0]);
		if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR)
			execve(av[0], av, envp);
		if (lstat(s2, &st) == 0 && st.st_mode & S_IXUSR)
			execve(s2, av, envp);
		if (!ft_strchr(s, ':'))
		{
			if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR)
				ft_putstr_fd("21sh: exec format error: ", 2);
			else if (lstat(av[0], &st) == 0)
				ft_putstr_fd("21sh: permission denied: ", 2);
			else if (!ft_strchr(s, ':'))
				ft_putstr_fd("21sh: command not found: ", 2);
			else
				ft_putstr_fd("21sh: no such file or directory: ", 2);
			ft_putendl_fd(av[0], 2);
			return ;
		}
	}
}
/*
void		ft_waitchild(char **av, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	close_termios();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
//		wait(&statval);
		waitpid(pid, &status, 0);
	}
	if (pid == 0)
		ft_exec(av, envp);
}*/
