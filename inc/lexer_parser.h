/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:07:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/08 15:58:56 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

typedef struct		s_token
{
	int				type;
	char			*word;
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

/*
**Ne pas changer l'ordre des tokens please
*/

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
	LR_DIR,		// "<>"
	DIR_L_AMP,	// "<&"
	DIR_R_AMP,	// ">&"
	O_BRACE, 	// "{ "
	C_BRACE, 	// "}"
	FD_IN,
	TARGET,
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

t_token				*create_token();
void				push_token();
void				clear_token();
void				destroy_token();

int					can_create_tree(t_token	*lst);
int					is_end(char *s, int *i, char c);
int					find_quote_end(char *s);
int					is_end(char *s, int *i, char c);

/*
 * PAS IMPLEMENTEES
t_cmd				*create_cmd();
void				push_cmd();
void				clear_cmd();
void				destroy_cmd();
 *
 */

#endif
