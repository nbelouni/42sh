/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:25:54 by alallema          #+#    #+#             */
/*   Updated: 2017/04/08 15:50:24 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>
# include <stdio.h>

int				exec_cmd(t_tree *root, t_lst *env);
int				ft_init_gpr(t_tree *root, t_lst *env);
int				ft_check_exec(char ***cmd);
int				ft_check_built(char **av);
int				ft_exec_built(char **args);

void			init_shell(void);
void			get_sig_ign(void);
void			wait_job(t_list *job_list);

void			ft_dot(t_tree *node, t_lst *env);
void			ft_pipe(t_tree *node, t_lst *env);
void			ft_or_and(t_tree *node, t_lst *env, int token);
void			ft_redir_right(t_tree *node, t_lst *env);
void			ft_exec_node(t_tree *node, t_lst *env);

void			print_tree(t_tree *root);
int				parse_builtins(t_core *core, char *cmd, char **cmd_args);

#endif
