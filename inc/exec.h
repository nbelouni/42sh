/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:25:54 by alallema          #+#    #+#             */
/*   Updated: 2017/03/08 13:04:21 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <signal.h>

int				exec_cmd(t_tree *root, t_lst *env);
int				ft_waitchild(t_tree *root, t_lst *env);
//void			ft_exec(char **s, t_lst *env);
int				ft_check_exec(char **cmd, t_lst *env);
int				ft_check_built(char **av);

void			ft_dot(t_tree *node, t_lst *env);
void	 		ft_pipe(t_tree *node, t_lst *env);
void			ft_or_and(t_tree *node, t_lst *env, int token);
void		 	ft_redir_right(t_tree *node, t_lst *env);
void			ft_exec_node(t_tree *node, t_lst *env);

#endif
