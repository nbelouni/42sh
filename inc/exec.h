/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:25:54 by alallema          #+#    #+#             */
/*   Updated: 2017/03/03 23:03:28 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>

int				exec_cmd(t_tree *root, t_lst *env);
int				ft_exec(char **s, t_lst *env);

#endif
