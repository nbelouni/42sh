/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:07:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/15 20:43:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

typedef struct		s_word
{
	char			*s;
	int				flag;
	struct s_word	*next;
}					t_word;

typedef struct		s_token
{
	int				type;
	int				n_word;
	t_word			*word;
	int				bt_level;	// Parenthese
	int				bc_level;	// Accolade
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

enum				e_flag
{
	N_QUOTE,
	S_QUOTE,
	D_QUOTE,
	BT_QUOTE
};

enum				e_token
{
	NO_TOKEN,
	BRACKET,	// "()"
	BRACE,		// "{} "
	DOT,		// ";"
	PIPE,		// '|"
	OR,			// '||"
	AND,		// '&&"
	START,		// "^, debut de ligne" -> utile ?
	SL_DIR,		// "<"
	DL_DIR,		// "<<"
	SR_DIR,		// ">"
	DR_DIR,		// ">>"
	AMP,		// "&"
	DIR_AMP,	// ">&"
	D_QUOTE,	// """
	S_QUOTE,	// "'"
	BT_QUOTE,	// "`"
};

typedef struct		s_cmd
{
	t_token			*prev_cmd;
	char			**cmd;
	int				in;
	int				out;
	struct s_cmd	*left;
	struct s_cmd	*right;
}					t_cmd;

int					create_word();
int					push_word();
int					clear_word();
int					destroy_word();

int					create_token();
int					push_token();
int					clear_token();
int					destroy_token();

/*
 * PAS IMPLEMENTEES
int					create_cmd();
int					push_cmd();
int					clear_cmd();
int					destroy_cmd();
 *
 */
#endif
