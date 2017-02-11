/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 12:30:14 by alallema          #+#    #+#             */
/*   Updated: 2017/02/11 23:50:26 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
/*
typedef struct		s_tok
{
	int				tok;
	int				pipefd[2];
}					t_tok;
*/
typedef struct		s_cmd
{
	t_bool			tokken;
	int				tok;
	char			**cmd;
	char			**arg;
}					s_cmd;

typedef struct		s_lst;
{
	void			*content;
	size_t			size;
	struct s_list	*prev;
	struct s_list	*next;
}					t_lst;

/*J'ai travailler sur mon 21 ..
 * travaille bien !!!
 * BISOUS
 * */
