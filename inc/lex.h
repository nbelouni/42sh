/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 12:30:14 by alallema          #+#    #+#             */
/*   Updated: 2017/04/08 21:16:20 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "42sh.h"

# define ISAMP(x) (x->type == DIR_L_AMP || x->type == DIR_R_AMP)
# define NEXTISCMD(x) (x->next->type == CMD || x->next->type == ARG)
# define PREVISCMD(x) (x->prev->type == CMD || x->prev->type == ARG)

typedef struct		s_pt
{
	int				i;
	int				len;
	int				type;
	int				level[2];
}					t_pt;

typedef struct		s_tok
{
	int				tok;
}					t_tok;

typedef struct		s_tree
{
	int				token;
	char			**cmd;
	t_token			*token_or;
	struct s_tree	*father;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct		s_lvl
{
	int				bt_lvl;
	int				bc_lvl;
}					t_lvl;

typedef struct		s_lib
{
	int				toke;
	int				priority;
}					t_lib;

int					is_char(char *s, int i, char c);
int					find_prev_char(char *s, int len, char c);
int					find_next_char(char *s, int len, char c);

int					is_group(char *s, int i);
int					is_separator(char *s, int i);
int					is_redirection(char *s, int i);
int					is_btquote(char *s, int i);
int					is_dquote(char *s, int i);
int					is_squote(char *s, int i);
int					is_new_btquote(char *s, int i);
int					is_backslash(char *s, int i);
int					is_any_quote(char *s, int i);
int					is_bracket(char *s, int i);
int					is_brace(char *s, int i);
int					is_space(char *s, int i);
int					is_dot(char *s, int i);
int					is_redir(char *s, int i);
int					is_agreg(char *s, int i);
int					is_or_and(char *s, int i);
int					is_quot(char *s, int i);

int					is_separator_type(int type);
int					is_open_group_type(int type);
int					is_close_group_type(int type);
int					is_dir_type(int type);
int					is_text_type(int type);

int					find_btquote_end(char *s, int i);
int					find_dquote_end(char *s, int i);
int					find_squote_end(char *s, int i);
int					find_group_end(char *s, int i, int token);
int					find_next_nbtq(char *s, int i);
int					find_dollar(char *s, int i);
int					find_new_btquote_end(char *s, int i);
int					find_next_inhibitor(char *s, int i, int *token);
int					find_next_btq(char *s, int i, int *token);
int					find_bracket_end(char *s, int i);

int					parse_buf(t_token **l, char *s, t_completion *c, t_lst *h);
int					cut_space(char *s, int i);
void				reset_int_pt(t_pt *pt);
int					parse_list(t_token **list, char *s, t_pt *p);
int					cut_cmd(t_token **list, char *s, t_pt *p);
int					check_tok(char *s, int l);
int					cut_quote(char *s, t_pt *p);
int					check_fd_out(t_token **list, char *s, t_pt *p);

void				ft_tokenadd(t_token **alst, t_token *new);
void				ft_tokenclear(t_token **lst);
void				ft_tokendestroy(t_token **begin);
t_token				*ft_tokenew(int type, char *word, int *level);
void				ft_tokenpush(t_token **begin, t_token *new);
void				sort_list_token(t_token **list, t_completion *c, t_lst *h);
int					ft_swap_in(t_token **list);
int					check_error_out(t_token *elem);
void				check_target_place(t_token **list);
void				ft_print_token_list(t_token **list);

int					return_new_prompt(int ret);
int					here_doc(t_token *elemi, t_completion *c, t_lst *hist);

t_tree				*creat_left(t_token *lst, t_lvl *lvl);
t_tree				*creat_right(t_token *lst, t_lvl *lvl);
void				ft_push_ast(t_token *list, t_tree **ast);
void				free_ast(t_tree *ast);
void				print_tab(char **tabol);
void				print_debug_ast(t_tree *node);
t_list				*concate_argv(t_token *lst);

#endif
