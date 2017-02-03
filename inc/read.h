/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:01:52 by alallema          #+#    #+#             */
/*   Updated: 2017/02/03 18:49:34 by nbelouni         ###   ########.fr       */
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
** touche de clavier
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
# define CTRL_L 12
# define CTRL_K 11
# define CTRL_W 23
# define CTRL_T 20
# define ALT_C  42947
# define ALT_V  10127586
# define ALT_X  8948194
# define ALT_R  1130044187
# define ALT_L  1146821403

# define PUT1(x) (ft_putstr_fd(x, 1));
# define PUT2(x) (ft_putstr_fd(x, 2));
# define E(x) (ft_putnbr_fd(x, 2));
# define X(x) (ft_putchar_fd(x, 2));
# define PROMPT_LEN 5

typedef struct	s_win
{
	int				col;
	int				row;
	int				letter;
}				t_win;

typedef struct	s_curs
{
	int col; // pos du curseur init = PROMPT_LEN
	int row; // pos du curseur 0
	int win_col;
	int win_row;
}				t_curs;

t_curs			g_curs;

typedef struct	s_term
{
	struct termios	old;
	struct termios	new;
}				t_term;

typedef struct	s_buf
{
	char		*line;
	int			size;
	char		*to_paste;
	int			to_paste_size;
}				t_buf;

t_buf			*init_buf(void);
void			free_buf(t_buf *buf);
void			clear_buf(t_buf *buf);

int				t_putchar(int i);
void			t_puts(char *s, int i);

int				init_termios(void);
int				close_termios(void);

int				read_line(t_buf *buf);

void			clean_pos_curs(void);
t_bool			init_curs(void);

void			get_sigwinch(int sig);
void			get_sigint(int sig);
t_bool			get_win();

size_t			calc_len(t_buf *buf, int x);
void			m_right(size_t len);
void			m_left(size_t len);
void			ft_del(size_t len);
//void			m_up(t_buf *buf, );
//void			m_down(t_buf *buf);
//void			m_home(t_buf *buf);
//void			m_end(t_buf *buf);
//void			m_ctrl_r(t_buf *buf);
//void			m_ctrl_l(t_buf *buf);

void			insert_in_buf(t_buf *buf, int cursor, char *s, size_t len);
void			delete_in_buf(t_buf *buf, int cursor, size_t len);

static void		(*tab_move[8])() = {
	[0] = m_right,
	[1] = m_left,
	[2] = ft_del,
//	[3] = m_down,
//	[4] = m_end,
//	[5] = m_home,
//	[6] = m_ctrl_r,
//	[7] = m_ctrl_l,
};
/*
[LEFT] -> calc_len + m_left;
RIGHT ->calc_len + m_right;
UP -> calc_len + m_left;
DOWN -> calc_len + m_right;
DEL -> calc_len + del + m_left;
RETR -> calc_len + del + m_left;
SUP  2117294875
HOME  4741915
END  4610843
PAGE_UP  2117425947
PAGE_DOWN  2117491483
TAB  9
CRTL  1
CTRL_D  4
CTRL_L 12
CTRL_K 11
CTRL_W 23
CTRL_T 20
ALT_C  42947
ALT_V  10127586
ALT_X  8948194
ALT_R  1130044187
ALT_L  1146821403
*/
/*
 * #define PROMPT_LEN	n
 * #define CURSOR_POS	(((row) * (max_col)) + col)// dans le tableau
 * struct affichage
 * {
 * .int col; // pos du curseur init = PROMPT_LEN
 * .int row; // pos du curseur 0
 * .int max_col;
 * .int max_row;
 * }
 * edition de ligne
 *
 * affichage :
 * .multiligne
 * .prendre en compte le prompt
 * .curseur
 * ->>> history
 * ->>> completion
 *
 * liste de fonction cursor:
 * left
 * right
 * home
 * end
 * ctr_l -> word
 * ctr_r -> word
 * ctr_up -> line
 * ctr_do -> line
 * 
 * modification de la chaine
 * insert
 * delete
 * cut before
 * cut after
 * paste
 * copy before
 * copy after
 *
*/

/* deplace le cursor
 * change indice cursor
 * delete cursor
 *
 * copy : 	tmp_buf = cut;
 * cut :	tmp_buf = cut;
 * 			del(buf->size)
 *
*/

#endif
