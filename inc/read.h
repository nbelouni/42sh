/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:01:52 by alallema          #+#    #+#             */
/*   Updated: 2017/04/08 19:16:52 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H
# include "42sh.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>

/*
** touches de clavier
*/
# define LEFT  4479771
# define RIGHT  4414235
# define UP  4283163
# define DOWN  4348699
# define ESC  27
# define SPACE  32
# define DEL  127
# define RETR  10
# define SUP  2117294875
# define HOME  4741915
# define END  4610843
# define PAGE_UP  2117425947
# define PAGE_DOWN  2117491483
# define TAB  9
# define CRTL  1
# define CTRL_D  4
# define TAB 9

/*
** cut word before
*/
# define CTRL_B 2

/*
** cut word after
*/
# define CTRL_E 5

/*
** cut before
*/
# define CTRL_K 11

/*
** cut after
*/
# define CTRL_W 23

/*
** copy word before
*/
# define CTRL_I 9

/*
** copy word after
*/
# define CTRL_N 14

/*
** copy before
*/
# define CTRL_A 1

/*
** copy after
*/
# define CTRL_F 6

/*
** paste
*/
# define CTRL_P 16

# define CTRL_T 20
# define ALT_C  42947
# define ALT_V  10127586
# define ALT_X  8948194
# define ALT_RIGHT  1130044187
# define ALT_LEFT  1146821403
# define ALT_UP 1096489755
# define ALT_DOWN 1113266971

# define PUT1(x) (ft_putstr_fd(x, 1));
# define PUT2(x) (ft_putstr_fd(x, 2));
# define E(x) (ft_putnbr_fd(x, 2));
# define X(x) (ft_putchar_fd(x, 2));

# define PROMPT1	"42sh.$ "
# define PROMPT2	"> "

typedef struct	s_win
{
	int				col;
	int				row;
	int				letter;
}				t_win;

typedef struct	s_curs
{
	int col;
	int row;
	int win_col;
	int win_row;
}				t_curs;

t_curs			g_curs;

typedef struct	s_term
{
	struct termios	old;
	struct termios	new;
}				t_term;

typedef struct	s_prompt
{
	char		*s;
	int			len;
}				t_prompt;

typedef struct	s_buf
{
	char		*line;
	char		*last_cmd;
	t_elem		*cur_hist;
	int			size;
	char		*to_paste;
	int			to_paste_size;
	char		*final_line;
	int 		istty;
}				t_buf;

/*
**	*********************************************************************
*/
/*
**	Fonctions de base ; struct t_buf
**	buf.c
*/

/*
**	Aloue t_buf en debut de programme
*/
t_buf			*init_buf(void);

/*
**	detruit t_buf en fin de programme
*/
void			free_buf(t_buf *buf);

/*
**	clear ligne a la fin d'une commande
*/
void			clear_buf(t_buf *buf);

/*
**	*********************************************************************
*/
/*
**	Fonctions base termcaps
**	term.c
*/

/*
**	Imprime un caractere, surcouchees dans d'autres fonctions
*/
int				t_putchar(int i);
/*
**	Imprime un caractere, surcouchees dans d'autres fonctions
*/
void			t_puts(char *s, int i);

/*
**	initialise termcaps,
**	appele a chaque edition de ligne
*/
int				init_termios(void);

/*
**	finit la phase termcaps,
**	appele apres chaque edition de ligne
*/
int				close_termios(void);

/*
**	*********************************************************************
*/
/*
**	Fonctions edition de ligne
**	read.c
*/

/*
**	Lit et edite ligne (visuel) + buffer (buf.line) si changements necessaires
*/
int				read_line(t_buf *buf, t_completion *completion, t_lst *hist);

/*
**	*********************************************************************
*/
/*
**	Fonctions base struct t_cursor
**	curs.c
*/

/*
**	Initialise curseur en debut de ligne, appele avant chaque "read_line()"
*/
void			clean_pos_curs(void);
/*
**	Premiere initialisation curseur, debut de programme
*/
t_bool			init_curs(void);

/*
**	*********************************************************************
*/
/*
**	Voir avec amelie
*/
void			get_sigwinch(int sig);
void			get_sigint(int sig);
t_bool			get_win();

/*
**	*********************************************************************
*/
/*
**	Fonctions base struct prompt
**	singleton pour qu'on puisse changer de prompt pendant l'execution
**	prompt.c
*/

/*
**	initialise prompt et le retourne
*/
t_prompt		manage_prompt(char *s, int num);

/*
**	retourne prompt.char *
*/
char			*get_prompt_str(void);

/*
**	retourne prompt.ft_strlen(char *)
*/
size_t			get_prompt_len(void);

/*
**	initialise prompt
*/
void			set_prompt(char *s, int len);

/*
**	calcule la longueur de la chaine a couper/coller/parcourir selon
**	caractere lut
**	calc_len.c
*/
size_t			calc_len(t_buf *buf, int x);

/*
**	*********************************************************************
*/
/*
**	Mouvements du curseur
**	edit_move.c
**	len = nombre de deplacements
*/

/*
**	deplace le curseur a droite
*/
void			m_right(size_t len);

/*
**	deplace le curseur a gauche
*/
void			m_left(size_t len);

/*
**	deplace le curseur en haut
*/
void			m_up(void);

/*
**	deplace le curseur en bas
*/
void			m_down(t_buf *buf);

/*
**	*********************************************************************
*/
/*
**	modifie la position du curseur et le buffer (buf.line) selon input
**	edit_visual.c
*/

/*
**	insere un caractere a curs.pos et bouge le curseur de 1 sur la droite
*/
int				vb_insert(t_buf *buf, char *s);

/*
**supprime le caractere a gauche de curs.pos et
**bouge le curseur de 1 sur la gauche
*/
void			vb_del(t_buf *buf, unsigned int x);

/*
**garde en memoire le caractere / mot / bout de ligne (selon input) buf.to_paste
*/
int				vb_copy(t_buf *buf, unsigned int x);

/*
**garde en memoire le caractere / mot / bout de ligne (selon input) buf.to_paste
**supprime la string de buf.line
*/
int				vb_cut(t_buf *buf, unsigned int x);

/*
**	insere buf.to_paste dans buf.line,
**	le curseur ne bouge pas
*/
int				vb_paste(t_buf *buf);

/*
**	*********************************************************************
*/
/*
**	Fonctions base edition du buffer
**	edit_buf.c
*/

/*
**	insere une string dans buf.line
*/
void			insert_in_buf(t_buf *buf, int cursor, char *s, size_t len);

/*
**	supprime une string dans buf.line
*/
void			delete_in_buf(t_buf *buf, int cursor, size_t len);

/*
**	copie  le caractere / mot / bout de ligne (selon input) de buf.line
**	dans buf.to_paste
*/
int				set_to_paste(t_buf *buf, int cursor, size_t len);

/*
**	copie  le caractere / mot / bout de ligne (selon input) de buf.to_paste
**	dans buf.line
*/
void			paste_in_buf(t_buf *buf, int cursor);

/*
**	*********************************************************************
*/
/*
**	imprime buf.line
**	edit_visual.c
*/
/*
**	imprime buf.line avant le curseur
*/
void			print_post_curs(t_buf *buf);
/*
**	imprime buf.line apres le curseur
*/
void			print_pre_curs(t_buf *buf);

/*
**	*********************************************************************
*/
/*
**	is_line_ended.c
**	si ligne finie :
**		met buf.line dans buf.final_line
**	sinon
**		concatene buf.final_line et buf.line
*/
int				is_line_ended(t_buf *buf);

typedef	struct s_token	t_token;

int				complete_final_line(t_buf *buf, t_token *lst);
int				edit_history(t_buf *buf, t_lst *history, int x);

#endif
