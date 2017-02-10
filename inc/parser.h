/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:42:32 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/10 18:26:52 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

typedef struct		s_cmd
{
	int				token;
	char			**args;
	int				intput;
	int				output;
	int				pid;
	int				ret;
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_cmd;

/*
typedef struct	s_manage_cmd
{
	int			token;
	int			input;
	int			output;
	int			pid;
}				t_manage_cmd;
*/

typedef enum	e_token
{
	NONE,
	S_QUOTE,
	BT_QUOTE,
	DEF_EXPR,	//define expression -> $()
	D_QUOTE,	
	BRACKET,
	BRACE,
	OR,
	PIPE,
	AND,
	AMP,
	SR_DIR,
	DR_DIR,
	SL_DIR,
	DL_DIR,
	AMP_DIR,
	DOT,
	SHARP,
	DOLLAR
}				t_token;
