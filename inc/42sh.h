/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:09:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/01 22:14:26 by nbelouni         ###   ########.fr       */
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
# include "exec.h"

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
	t_elem			*head;
	t_elem			*tail;
	t_lst			*env;
}					t_set;


/*
**	ft_builtin_cd.c
*/

int					ft_builtin_cd(t_lst *env, char *cmd, char **args);

/*
**	ft_builtin_echo.c
*/

int					ft_builtin_echo(t_lst *env, char *cmd, char **args);

/*
**	ft_builtin_env.c
*/

t_lst				*ft_lstdup(t_lst *to_dup);
int					ft_builtin_env(t_lst *env, char *cmd, char **args);

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
void				ft_add_elem(t_elem *elem, t_lst *lst);
void				ft_del_elem(t_elem **elem, t_lst *lst);
t_elem				*ft_find_elem(char *name, t_lst *lst);
t_elem				*ft_new_elem(char *str);

/*
**	ft_norm_tools.c
*/

void				ft_del_list(t_lst *lst);
int					ft_pwd_swap(t_lst *env, char *owd, char *cwd);

/*
**	ft_opt_parse.c
*/

int					*ft_opt_parse(int *opt, char *opts, char **args, int i);

#endif
