/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:07:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/27 15:02:48 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

typedef struct		s_word
{
	char			*s;
	int				flag;
	int				level;
	struct s_word	*next;
	struct s_word	*prev;
}					t_word;

typedef struct		s_token
{
	int				type;
	char			*word;
	int				n_string;
	t_word			*string;
	int				bt_level;	// Parenthese
	int				bc_level;	// Accolade
	int				select;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

enum				e_flag
{
	NO_QUOTE,
	S_QUOTE,
	D_QUOTE,
	OBT_QUOTE,	// "$("
	BT_QUOTE
};

/*Ne pas changer l'ordre des tokens please*/
enum				e_token
{
	NO_TOKEN,
	CMD,
	ESPACE,
	O_BRACKET,	// "("
	C_BRACKET,	// ")"
	DOT,		// ";"
	PIPE,		// '|"
	START,		// "^, debut de ligne" -> utile ?
	SL_DIR,		// "<"
	SR_DIR,		// ">"
	AMP,		// "&"
	OR,			// '||"
	AND,		// '&&"
	DL_DIR,		// "<<"
	DR_DIR,		// ">>"
	DIR_AMP,	// ">&"
	O_BRACE, 	// "{ "
	C_BRACE, 	// "}"
	FD_IN,
	FD_OUT,
	ARG
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

t_word				*create_word();
void				push_word();
void				clear_word();
void				rm_word(t_word **cmd);
int					count_word(t_word *w);
void				destroy_word();

t_token				*create_token();
void				push_token();
void				clear_token();
void				destroy_token();

int					can_create_tree(t_token	*lst);
/*
 * PAS IMPLEMENTEES
t_cmd				*create_cmd();
void				push_cmd();
void				clear_cmd();
void				destroy_cmd();
 *
 */



#endif
