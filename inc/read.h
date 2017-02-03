/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:01:52 by alallema          #+#    #+#             */
/*   Updated: 2017/02/03 14:32:59 by nbelouni         ###   ########.fr       */
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
# define PROMPT_LEN 0

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

void			m_right(t_buf *buf);
void			m_left(t_buf *buf);
void			m_up(t_buf *buf);
void			m_down(t_buf *buf);
void			m_home(t_buf *buf);
void			m_end(t_buf *buf);
void			m_ctrl_r(t_buf *buf);
void			m_ctrl_l(t_buf *buf);

void			insert_c(t_buf *buf, int cursor, char c);
void			delete_c(t_buf *buf, int cursor);

static void		(*tab_move[8])() = {
	[0] = m_right,
	[1] = m_left,
	[2] = m_up,
	[3] = m_down,
	[4] = m_end,
	[5] = m_home,
	[6] = m_ctrl_r,
	[7] = m_ctrl_l,
};

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

#endif
