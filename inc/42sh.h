/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:09:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 15:46:08 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include <stdlib.h>
# include <sys/syslimits.h>
# include "libft.h"
# include "options.h"

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

# include "completion.h"
# include "read.h"
# include "lexer_parser.h"
# include "lex.h"
# include "exec.h"
# include "globbing.h"

# define END_EOT	18

typedef struct		s_elem
{
	char			*name;
	char			*value;
	unsigned int	is_appended;
	unsigned int	is_modified;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

typedef struct		s_lst
{
	size_t			size;
	t_elem			*head;
	t_elem			*tail;
}					t_lst;

typedef struct		s_core
{
	t_lst			*set;
	t_lst			*hist;
	t_lst			*env;
	t_lst			*exp;
}					t_core;

<<<<<<< HEAD
/*	A REFAIRE
**	ft_default_set.c
*/

t_lst				*ft_init_lstset(void);

/*
**				init_default_env
*/

t_lst				*ft_default_env(void);

/*
**	ft_init.c
*/

t_core				*ft_core_alloc(void);
t_lst				*ft_init_list(void);
t_elem				*ft_init_elem(void);
char				**ft_env_to_tab(t_lst *lst);
t_lst				*ft_env_to_list(char **envp, t_lst *lst);

/*
**	ft_builtin_cd.c
*/

int					ft_free_and_return(int ret, void *d1, void *d2, void *d3);
int					ft_builtin_cd(t_lst *env, char *cmd, char **args);

/*
**	ft_builtin_echo.c
*/

int					ft_builtin_echo(t_lst *env, char *cmd, char **args);

/*
**	ft_builtin_env.c
*/

int					ft_builtin_env(t_lst *env, char **args);

/*
**	ft_builtin_exit.c
*/

int					ft_builtin_exit(t_core *core, char *cmd, char **args);

/*
**	ft_builtin_history.c
*/

int					ft_builtin_history(t_lst *set, t_lst *hist, char **args);

/*
**	ft_builtin_setenv.c
*/

int					ft_setenv(t_lst *env, char *var, char *word);
int					ft_builtin_setenv(t_lst *env, char *cmd, char **args);
=======
# include "builtins.h"
# include "history.h"
>>>>>>> 20d92ba433e91b502b84dff298e1ba3078fda93b

/*
**	ft_default_set.c
*/

t_lst				*ft_init_lstset(void);


<<<<<<< HEAD
=======
t_core				*ft_init_core(void);
t_lst				*ft_init_list(void);
t_elem				*ft_init_elem(void);
char				**ft_env_to_tab(t_lst *lst);
t_lst				*ft_env_to_list(char **envp, t_lst *lst);
>>>>>>> 20d92ba433e91b502b84dff298e1ba3078fda93b

/*
**	ft_list_tools.c
*/

void				ft_print_lst(t_lst *lst);
void				ft_insert_elem(t_elem *elem, t_lst *lst);
int					ft_add_elem(t_lst *lst, char *s);
void				ft_del_elem(t_elem **elem, t_lst *lst);
t_elem				*ft_find_elem(char *name, t_lst *lst);
t_elem				*ft_new_elem(char *str);
void 				ft_extract_elem(t_elem **elem, t_lst *lst);


/*
**	ft_list_tools2.c
*/

void				ft_lstclr(t_lst *lst);
t_elem				*ft_get_nelem(t_lst *lst, int n);
t_lst				*ft_lstcpy(t_lst *dst, t_lst *src);
t_elem				*ft_elemdup(t_elem *elem1);
t_lst				*ft_lstdup(t_lst *to_dup);

/*
**	ft_list.c
*/

int					ft_export(t_lst *dup, char *arg);

/*
**	ft_norm_tools.c
*/

void				ft_del_list(t_lst *lst);
int					ft_pwd_swap(t_lst *env, char *owd, char *cwd);


#endif
