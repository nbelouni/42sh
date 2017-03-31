/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:07:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/31 16:18:01 by nbelouni         ###   ########.fr       */
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

t_token				*create_token();
void				push_token();
void				clear_token();
void				destroy_token();

int					can_create_tree(t_token	*lst);
int					is_end(char *s, int *i, char c);
int					find_quote_end(char *s);


#endif
