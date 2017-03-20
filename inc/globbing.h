/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:31:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/20 17:47:25 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GLOBBING_H
# define GLOBBING_H

#include "42sh.h"

typedef struct			s_reg_paths
{
	char				*path;
	struct s_reg_paths	*match;
	struct s_reg_paths	*next;
}						t_reg_paths;

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
int						edit_cmd(t_token *list, t_lst *env);
int						regex(t_token *lst);
t_token					*find_expansions(t_token *lst);
void					expand_args(t_token **list, t_token **elem);

#endif
