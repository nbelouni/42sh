/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:12:19 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:12:38 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/*
**	ft_get_history.c
*/

char	*ft_get_hist_value(t_elem *elem, int type);
int		ft_get_hsize(t_core *core);
t_lst	*ft_histfile_to_histlist(t_lst **histlist, int fd);
int		ft_get_histfile_content(t_lst *hist, int fd);
t_lst	*ft_get_history(t_lst *hist, char *filename);

/*
**	ft_histopt_args.c
*/

int		ft_histopt_p(t_lst *hist, char **args);
int		ft_histopt_s(t_lst *hist, char **args);

/*
**	ft_histopt_filename.c
*/

int		ft_histopt_n(t_core *core, char *filename);
int		ft_histopt_w(t_core *core, char *filename);
int		ft_histopt_a(t_core *core, char *filename);
int		ft_histopt_r(t_core *core, char *filename);

/*
**	ft_histopt_offset.c
*/

int		ft_del_hist_offset(t_lst *hist, char *arg);
int		ft_histopt_d(t_lst *hist, char *arg);

/*
**	ft_history_opt.c
*/

t_lst	*ft_histopt_c(t_lst *hist);
int		ft_check_histopt_arg(t_lst *hist, char **args, int i);
int		ft_check_histopt_offset(t_lst *hist, char **args, int i);
int		ft_check_histopt_file(t_core *core, char **args, int i);
int		ft_check_histopt(t_core *core, char **args, int i);
int		ft_parse_histopt(t_core *core, char **args);

/*
**	ft_history_tools.c
*/

int		ft_truncate_histlist(t_lst *hist, size_t n);
int		ft_truncate_histfile(char *filename, int n);
char	*ft_get_hfname(t_core *core);
char	*ft_check_hist_filename(t_core *core, char *filename);
int		ft_print_history(t_lst *hist, int start);
int		ft_cmd_to_history(t_lst *hist, char *cmd);
int		ft_check_history_var(t_core *core);
int		ft_print_histopt_err(char c);

/*
**	ft_set_history.c
*/

int		ft_get_hfsize(t_core *core);
int		ft_histlist_to_histfile(t_lst **hist, int fd);
int		ft_check_histfile(t_lst *hist, char *filename);
int		ft_set_history(t_lst *hist, char *filename);

/*
**	ft_bang_alphanum_sub.c
*/

int		bang_number_sub(t_lst *hist, char **s, char *n);
int		bang_start_occur_sub(t_lst *hist, char **s, char *n);
int		bang_contain_occur_sub(t_lst *hist, char **s, char *n);

/*
**	ft_bang_special_sub.c
*/

int		bang_doll_sub(char *name, char **s);
int		dbang_sub(t_lst *hist, char **s);
int		bang_wildcard_sub(char *name, char **s);
int		bang_diese_sub(char **s, int i);

/*
**	ft_bang_substitution.c
*/

int		print_sub(t_lst *hist, char **s, int *i);
int		switch_bang(t_lst *hist, char **s, int *i);
int		bang_substitution(char **s, t_core *core);

/*
**	ft_quick_substitution.c
*/

int		ft_quicksub_with_args2(t_elem *tail, char *tmp, char *p, char **s);
int		ft_quicksub_with_args(t_elem *tail, char **s, int *i);
int		ft_exec_quick_sub(t_elem *tail, char **s, int *i);

/*
**	expansions
*/

char	*ft_gets_lastcmd(t_lst *hist);
char	*ft_gets_hist_ncmd(t_lst *hist, int n);
char	*ft_gets_quicksub(t_lst *hist, char *search, char *replace);
char	*ft_gets_until_now(char *s, char *ptr);
char	*ft_gets_firstword(char *str);
char	*ft_gets_lastword(char *str);
int		ft_strstr_bis(char *s1, char *s2, int n);
int		ft_strncmp_bis(char *s1, char *s2, int n);
char	*ft_gets_in_hist(t_lst *hist, char *s, int (*f)(char *, char *, int));
char	*find_number(char *s);
char	*find_replace_cmd(char *s);
char	*ft_gets_cmd_except_firstword(char *str);

#endif
