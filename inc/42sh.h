/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:09:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/11 18:54:10 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include <stdlib.h>
# include <sys/syslimits.h>
# include "libft.h"

# define CD_OPT		"LP"
# define ENV_OPT	"i"
# define EXPORT_OPT	"p"
# define UNSET_OPT	"fv"
# define HIST_OPT	"cdanrwps"

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

# include "completion.h"
# include "read.h"
# include "lexer_parser.h"
# include "lex.h"
# include "job.h"
# include "globbing.h"

# define END_EOT	18

typedef struct		s_elem
{
	char			*name;
	char			*value;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

typedef struct		s_lst
{
	size_t			size;
	t_elem			*head;
	t_elem			*tail;
}					t_lst;

typedef struct		s_set
{
	t_lst			*set;
	t_lst			*env;
}					t_set;


/*
**	ft_builtin_cd.c
*/

int					ft_free_and_return(int ret, void *start, ...);
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

int					ft_builtin_exit(t_lst *env, char *cmd, char **args);

/*
**	ft_builtin_setenv.c
*/

int					ft_setenv(t_lst *env, char *var, char *word);
int					ft_builtin_setenv(t_lst *env, char *cmd, char **args);

/*
**	ft_builtin_unsetenv.c
*/

int					ft_unsetenv(t_lst *env, char *var);
int					ft_builtin_unsetenv(t_lst *env, char *cmd, char **args);

/*
**	ft_init.c
*/

t_set				*ft_init_set(void);
t_lst				*ft_init_list(void);
t_elem				*ft_init_elem(void);
char				**ft_env_to_tab(t_lst *lst);
t_lst				*ft_env_to_list(char **envp, t_lst *lst);

/*
**	ft_list_tools.c
*/

void				ft_print_lst(t_lst *lst);
void				ft_insert_elem(t_elem *elem, t_lst *lst);
int					ft_add_elem(t_lst *lst, char *s);
void				ft_del_elem(t_elem **elem, t_lst *lst);
t_elem				*ft_find_elem(char *name, t_lst *lst);
t_elem				*ft_new_elem(char *str);

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

/*
**	ft_opt_parse.c
*/

int					*ft_opt_parse(char *opts, char **args, size_t overwrite);

#endif
