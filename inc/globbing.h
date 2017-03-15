/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:31:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/13 19:19:08 by nbelouni         ###   ########.fr       */
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

int						edit_cmd(t_token *list, t_lst *env);
int						regex(char *s);
char					**find_expansions(char **s);
int						is_comma(int *lex, int len, int max_lvl);

#endif
