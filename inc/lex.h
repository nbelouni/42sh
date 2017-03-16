/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 12:30:14 by alallema          #+#    #+#             */
/*   Updated: 2017/03/15 23:55:35 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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

typedef struct s_lvl
{
	int 					bt_lvl;
	int					 	bc_lvl;
}							t_lvl;

typedef struct  s_lib
{
	int 			toke;
	int 			priority;
}						t_lib;
/*
enum				e_token2
{
	O_BRACKET,	// "("
	C_BRACKET,	// ")"
	O_BRACE, 	// "{ "
	C_BRACE, 	// ";}"
	OBT_QUOTE,	// "$("
	CBT_QUOTE,	// ")" -> == C_BRACKET
	COMMENT		// " #"
};
*/

/*
**	return == len de la chaine a strsub -> strsub(s, i, is_*());
*/
int		is_char(char *s, int i, char c);
int		find_prev_char(char *s, int len, char c);
int		find_next_char(char *s, int len, char c);

int		is_group(char *s, int i);
int		is_separator(char *s, int i);
int		is_redirection(char *s, int i);
int		is_btquote(char *s, int i);
int		is_dquote(char *s, int i);
int		is_squote(char *s, int i);
int		is_new_btquote(char *s, int i);
int		is_backslash(char *s, int i);
int		is_any_quote(char *s, int i);

int		find_btquote_end(char *s, int i);
int		find_dquote_end(char *s, int i);
int		find_squote_end(char *s, int i);
int		find_group_end(char *s, int i, int token);
int		find_next_nbtq(char *s, int i);
int		find_dollar(char *s, int i);
int		find_new_btquote_end(char *s, int i);
int		find_next_inhibitor(char *s, int i, int *token);
int		find_next_btq(char *s, int i, int *token);
/*
int		add_no_quote(char *s, int *i, t_word **lst);
int		add_squote(char *s, int *i, t_word **lst);
int		add_dquote(char *s, int *i, t_word **lst, int where);
int		add_new_btquote(t_word *tmp, int *i, t_word **lst);
int		add_btquote(t_word *tmp, int *i, t_word **lst);

int		lex_buf(char *s, t_word **lst);
*/
int		is_bracket(char *s, int i);
int		is_brace(char *s, int i);
int		is_space(char *s, int i);
int		is_dot(char *s, int i);
int		is_redir(char *s, int i);
int		is_agreg(char *s, int i);
int		is_or_and(char *s, int i);
int		is_quot(char *s, int i);
int		find_bracket_end(char *s, int i);

int		parse_buf(t_token **lst, char *s, t_completion *completion);
int		cut_space(char *s, int i);
void	reset_int_pt(t_pt *pt);
int		parse_list(t_token **list, char *s, t_pt *p);
int		cut_cmd(t_token **list, char *s, t_pt *p);
int		check_tok(char *s, int l);
int		cut_quote(char *s, t_pt *p);
int		check_fd_out(t_token **list, char *s, t_pt *p);

void	ft_tokenadd(t_token **alst, t_token *new);
void	ft_tokenclear(t_token **lst);
void	ft_tokendestroy(t_token **begin);
t_token	*ft_tokenew(int type, char *word, int *level);
void	ft_tokenpush(t_token **begin, t_token *new);
int		sort_list_token(t_token **list, t_completion *completion);
void	ft_print_token_list(t_token **list);
/*
int		add_new_word(t_word *w, int len, t_word **lst);
*/
int		is_separator_type(int type);
int		is_open_group_type(int type);
int		is_close_group_type(int type);
int		is_dir_type(int type);
int		is_text_type(int type);

int		return_new_prompt(int ret);
/*
**       ast
*/
int		here_doc(t_token *elemi, t_completion *completion);

t_tree 	*creat_left(t_token *lst, t_lvl *lvl);
t_tree 	*creat_right(t_token *lst, t_lvl *lvl);
void 		ft_push_ast(t_token *list, t_tree **ast);
void 		free_ast(t_tree *ast);
void 		print_debug_ast(t_tree *node);

t_token		*is_local_var(t_token *lst);
/*
void	ft_cmdadd(t_cmd **alst, t_cmd *new);
void	ft_cmdclear(t_cmd **cmd);
void	ft_cmdestroy(t_cmd **begin);
t_cmd	*ft_cmdnew(int token, char *cmd);
void	ft_cmdpush(t_cmd **begin, t_cmd *new);
*/
/*
 * . pour les ouvrants/fermants, compter 2 motifs differents
 *
 * Renvoie une portion du buffer separee par group && separators
 * . appelle is_group(), is_closed()
 * int		get_complete_group(char **group);
 *
 * Renvoie une portion du buffer separee par group && separators
 * . appelle is_group(), is_closed() et is_separator()
 * char		*get_complete_cmd();
 *
 * renvoie le type d'une portion d'une commande (cmd || arg || redirection)
 * complete et set *token
 * e_type	get_args(char **token);
 *
 * t_cmd	*set_cmd();
 *
 * lst functions;
 *
 * Quand tout ca est fait, GROS CHECK :
 * int		can_parse();
 * if (TRUE)
 * 	return (lst);
 * return (NULL);
*/
