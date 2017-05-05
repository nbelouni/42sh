/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:02:12 by llaffile          #+#    #+#             */
/*   Updated: 2017/05/05 18:53:23 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define OPEN	1
# define CLOSE	2
# define DUP	4
# define WRITE	8

typedef struct	s_io
{
	int		flag;
	int		mode;
	int		dup_src;
	int		dup_target;
	int		tab_fd[3];
	char	*str;
}				t_io;

typedef struct	s_mode
{
	int		redir;
	int		mode;
	int		flag;
}				t_mode;

typedef struct	s_redir
{
	char	*redir;
	int		mode;
}				t_redir;

t_io		*new_io();
char		*copy_redir(t_io *io);
char		*copy_process(t_process_p process);
char		*ft_fix_join(char *s, char *buf);
int			list_iter_int(t_list *list, int (*f)(void *, int), int d);
int			apply_redir(t_io *io, int dofork);
int			restore_fd(t_io *io, int dofork);
int			is_builtin(char **args);
int			save_fd(t_io *io, int type_redir, int dofork);
int			list_int2(t_list *list, int (*f)(void *, int, int), int d, int t);

#endif
