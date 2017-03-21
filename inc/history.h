/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:36:55 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/21 15:54:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef enum	e_bang
{
	N_BANG,
	N_LESS_BANG,
	DOUBLE_BANG,
	SSTART_BANG,
	PRINT_SSTART_BANG,
	SCONTAIN_BANG,
	UNTIL_NOW_BANG,
	RUN_LAST_BANG,
	RUN_EXCEPT_FIRST_BANG,
	PRINT_LAST_BANG,
	PRINT_EXCEPT_FIRST_BANG,
	QUICK_SUB

}				t_bang;

/*
**	ft_builtin_history.c
*/

int			ft_builtin_history(t_lst *set, t_lst *hist, char **args);

/*
**	ft_get_history.c
*/

char		*ft_get_hist_value(t_elem *elem, int type);
int			ft_get_hsize(t_lst *set);
t_lst		*ft_histfile_to_histlist(t_lst *histlist, int fd);
int			ft_get_histfile_content(t_lst *hist, int fd);
t_lst		*ft_get_history(t_lst *hist, char *filename);

/*
**	ft_histopt_args.c
*/

int			ft_histopt_p(t_lst *hist, char **args);
int			ft_histopt_s(t_lst *hist, char **args);

/*
**	ft_histopt_filename.c
*/

int			ft_histopt_n(t_lst *set, t_lst *hist, char *filename);
int			ft_histopt_w(t_lst *set, t_lst *hist, char *filename);
int			ft_histopt_a(t_lst *set, t_lst *hist, char *filename);
int			ft_histopt_r(t_lst **hist, t_lst *set, char *filename);

/*
**	ft_histopt_offset.c
*/

int			ft_del_hist_offset(t_lst *hist, char *arg);
int			ft_histopt_d(t_lst *hist, char *arg);

/*
**	ft_history_opt.c
*/

t_lst		*ft_histopt_c(t_lst *hist);
int			ft_check_histopt_arg(t_lst *hist, char **args, int i);
int			ft_check_histopt_offset(t_lst *hist, char **args, int i);
int			ft_check_histopt_file(t_lst *set, t_lst *hist, char **args, int i);
int			ft_check_histopt(t_lst *set, t_lst *hist, char **args, int i);
int			ft_parse_histopt(t_lst *set, t_lst *hist, char **args);

/*
**	ft_history_tools.c
*/

int			ft_truncate_histlist(t_lst *hist, size_t n);
int			ft_truncate_histfile(char *filename, int n);
char		*ft_get_hfname(t_lst *set);
char		*ft_check_hist_filename(t_lst *set, char *filename);
int			ft_print_history(t_lst *hist, int start);
int			ft_cmd_to_history(t_lst *hist, char *cmd);
int			ft_check_history_var(t_lst *set, t_lst *hist);
int			ft_print_histopt_err(char c);

/*
**	ft_set_history.c
*/

int			ft_get_hfsize(t_lst *set);
int			ft_histlist_to_histfile(t_lst **hist, int fd);
int			ft_check_histfile(t_lst *hist, char *filename);
int			ft_set_history(t_lst *hist, char *filename);

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

#endif
