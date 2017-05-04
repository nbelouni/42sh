/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:11:47 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:11:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*
**	Chaque builtin a pour appelation "ft_builtin_<nom du builtin>.c",
**	leurs parametres sont t_core *core et char **args, args ne contenant
**	pas le nom du builtin.
*/

/*
**	ft_builtin_bang.c
*/

int		ft_strstr_bis(char *s1, char *s2, int n);
int		ft_strncmp_bis(char *s1, char *s2, int n);
char	*ft_gets_cmd_except_firstword(char *str);
char	*ft_gets_lastword(char *str);
char	*ft_gets_in_hist(t_lst *hist, char *s, int (*f)(char *, char *, int));

/*
**	ft_builtin_bang2.c
*/

char	*find_replace_cmd(char *s);
char	*ft_gets_lastcmd(t_lst *hist);
char	*ft_gets_hist_ncmd(t_lst *hist, int n);
char	*ft_gets_quicksub(t_lst *hist, char *search, char *replace);
char	*ft_gets_until_now(char *s, char *ptr);

/*
**	ft_builtin_bang3.c
*/

char	*find_number(char *s);

/*
**	ft_builtin_bg.c
*/

int		ft_builtin_bg(t_core *core, char **args);

/*
**	ft_builtin_cd.c
*/

char	*ft_concat_path(char *res, char *s1, char *s2, size_t len);
int		ft_builtin_cd(t_core *core, char **args);

/*
**	ft_builtin_cd2.c
*/

char	*ft_switch_path(char *s1, char *s2);
char	*ft_create_oldpath(char *f_path, t_lst *env);
char	*ft_create_absolute_path(char *f_path, char *arg1);
char	*ft_create_path2(t_lst *env, char *arg1);
char	*ft_create_path(t_lst *env, char *arg1, char *arg2);

/*
**	ft_builtin_cd3.c
*/

void	supp_file(char **files);
int		file_len(char **files);
char	*concat_path(char *s);

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
**	ft_builtin_locale.c
*/

int		ft_builtin_locale(t_core *core, char **args);

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
