/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:31:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:44:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include "42sh.h"

typedef struct s_core	t_core;

typedef struct			s_reg_path
{
	char				*path;
	char				*out;
	int					level;
	t_bool				is_abs;
	struct s_reg_path	*next;
	struct s_reg_path	*prev;
}						t_reg_path;

typedef enum			e_sequence_type
{
	NO_SQ_TYPE,
	ALPHA,
	NUMERIC
}						t_sequence_type;

typedef struct			s_exp
{
	char				*first_word;
	char				**poss;
	int					n_poss;
	char				*last_word;
	int					type;
}						t_exp;

int						is_end(char *s, int *i, char c);
int						is_begin(char *s, int *i, char c);
int						is_regex(char *s, int i);
int						is_comma(int *lex, int len, int max_lvl);
int						is_exp(char *s, int *pivot, int *begin, int *end);
int						is_sequence(char *s, int *pivot, int *begin, int *end);
int						which_sequence_type(char *s, int begin, int end, int p);
int						find_last_len(char *s);
int						can_skip_char(char *s, int i);
int						count_slashs(char *s);
int						is_regex_in_text(char *s);

int						find_pivot(char *s, int begin, char c);
int						find_begin(char *s, int pivot);
int						find_end(char *s, int pivot);
int						find_n_poss(char *s, int end);
int						find_len(char *s, int end);

int						free_rg_and_return(char **rg, int ret);
int						init_bg_end_type(char *s, int *begin, int *end);

int						can_expand(char *s);
int						edit_cmd(char ***args, t_core *core);
t_reg_path				*replace_regex(char *s);
t_token					*expand_text(t_exp *exp, t_token *lst);
int						find_sequence(char *s, t_exp *exp);
void					final_tmp(t_token **t1, t_token **t2,
						t_token *t3, t_exp *exp);
t_token					*replace_expansions(t_token *lst);
void					expand_args(t_token **list, t_token **elem);

t_reg_path				*ft_reg_pathnew(char *p, char *o, int l, t_bool out);
void					ft_reg_pathadd(t_reg_path **begin, t_reg_path *new);
void					ft_reg_pathclear(t_reg_path **list);
void					ft_reg_pathpush(t_reg_path **begin, t_reg_path *new);
void					ft_reg_pathdestroy(t_reg_path **begin);
int						which_quotes(char *s, int len);
int						init_exp_sq(char **sq, int type, t_exp *exp);
void					clean_t_exp(t_exp *exp);
int						find_exp(char *s, t_exp *exp);
int						which_sequence_type(char *s, int a, int b, int c);

int						find_regex(t_reg_path **c, t_reg_path **r,
						char *s, int n);
int						match_regex(char *s, char *rg_ref);
int						regexp_in_tree(t_tree *node, t_core *env);

#endif
