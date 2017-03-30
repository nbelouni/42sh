/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:31:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 11:11:22 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GLOBBING_H
# define GLOBBING_H

#include "42sh.h"

typedef struct	s_core	t_core;

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
int						is_comma(int *lex, int len, int max_lvl);
int						is_exp(char *s, int *pivot, int *begin, int *end);
int						is_sequence(char *s, int *pivot, int *begin, int *end);
int						which_sequence_type(char *s, int begin, int end, int p);
int						is_regex_in_text(char *s);

int						can_expand(char *s);
int						edit_cmd(char ***args, t_core *core);
t_reg_path				*replace_regex(char *s);
t_token					*find_expansions(t_token *lst);
void					expand_args(t_token **list, t_token **elem);

t_reg_path				*ft_reg_pathnew(char *p, char *o, int l, t_bool out);
void					ft_reg_pathadd(t_reg_path **begin, t_reg_path *new);
void					ft_reg_pathclear(t_reg_path **list);
void					ft_reg_pathpush(t_reg_path **begin, t_reg_path *new);
void					ft_reg_pathdestroy(t_reg_path **begin);
int						which_quotes(char *s, int len);

#endif
