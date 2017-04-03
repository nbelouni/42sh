/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:39:57 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/20 14:40:25 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** env par defaut
*/
t_lst	*ft_default_env(void)
{
	t_lst	*env;
	char *pwd;

	pwd = NULL;
	if (!(env = ft_init_list()))
		return (NULL);
	if (!(pwd = getcwd(NULL, PATH_MAX)))
	{
		ft_memdel((void*)&env);
		return (NULL);
	}
	ft_setenv(env, "PWD", pwd);
	ft_setenv(env, "SHLVL", "1");
	ft_setenv(env, "_", NULL);
	ft_strdel(&pwd);
	return (env);
}

/*
**	ft_init_lstset est une fonction qui va initialiser la liste du set
**	avec les variables HISTFILE, HISTSIZE et HISTFILESIZE, définis sur
**	les standards de bash.
*/

t_lst	*ft_init_lstset(void)
{
	t_lst	*set;
	char	*pwd;
	char	*histfilepath;

	pwd = NULL;
	histfilepath = NULL;
	set = NULL;
	if ((set = ft_init_list()) == NULL)
		return (NULL);
	if ((pwd = getcwd(NULL, PATH_MAX)) == NULL)
	{
		free(set);
		return (NULL);
	}
	if ((histfilepath = ft_strnew((ft_strlen(pwd) + 15))) == NULL)
		return (NULL);
	ft_strcpy(histfilepath, pwd);
	histfilepath = ft_strcat(histfilepath, "/.42sh_history");
	ft_setenv(set, "HISTFILE", histfilepath);
	ft_multi_free(pwd, histfilepath, NULL, NULL);
	ft_setenv(set, "HISTSIZE", "500");
	ft_setenv(set, "HISTFILESIZE", "500");
	return (set);
}
