/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:25:54 by alallema          #+#    #+#             */
/*   Updated: 2017/03/06 14:01:20 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "42sh.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>

int				exec_cmd(t_tree *root, t_lst *env);
int				ft_exec(char **s, t_lst *env);

#endif
