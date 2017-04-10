/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:39:50 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/29 19:06:26 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// typedef int (*builtin_exec)(t_core *, char **);

typedef struct	s_builtin_array
{
	char		*cmd;
	int			(* const func)(t_core *, char **);
}				t_builtin_array;

// typedef enum builtin_table
// {
// 	B_ENV,
// 	B_SETENV,
// 	B_UNSETENV,
// 	B_UNSET,
// 	B_EXPORT,
// 	B_EXIT,
// 	B_CD,
// 	B_ECHO,
// 	B_JOBS,
// 	B_BG,
// 	B_FG,
// 	B_HISTORY,
// };

/*
**	Chaque builtin a pour appelation "ft_builtin_<nom du builtin>.c",
**	leurs parametres sont t_core *core et char **args, args ne contenant
**	pas le nom du builtin.
*/

int		ft_free_and_return(int ret, void *d1, void *d2, void *d3);

/*
**	ft_builtin_bg.c
*/

int		ft_builtin_bg(t_core *core, char **args);

/*
**	ft_builtin_cd.c
*/

int		ft_builtin_cd(t_core *core, char **args);

/*
**	ft_builtin_echo.c
*/

int		ft_builtin_echo(t_core *core, char **args);

/*
**	ft_builtin_env.c
*/

int		ft_builtin_env(t_core *core, char **args);

/*
**	ft_builtin_exit.c
*/

int		ft_builtin_exit(t_core *core, char **args);

/*
**	ft_builtin_export.c
*/

void	move_to_env(t_elem *lst, t_lst *env, t_lst *type_env);
void	ft_print_export(t_core *m_env);
int		ft_add_elemo(t_lst *lst, char *s);
int		ft_builtin_export(t_core *core, char **args);

/*
**	ft_builtin_fg.c
*/

int		ft_builtin_fg(t_core *core, char **args);

/*
**	ft_builtin_history.c
*/

int		ft_builtin_history(t_core *core, char **args);

/*
**	ft_builtin_jobs.c
*/

int		ft_builtin_jobs(t_core *core, char **args);

/*
**	ft_builtin_setenv.c
*/

int		ft_setenv(t_lst *env, char *var, char *word);
int		ft_builtin_setenv(t_core *core, char **args);

/*
**	ft_builtin_unset.c
*/

int		ft_builtin_unset(t_core *core, char **args);

/*
**	ft_builtin_unsetenv.c
*/

int		ft_unsetenv(t_lst *env, char *var);
int		ft_builtin_unsetenv(t_core *core, char **args);

#endif
