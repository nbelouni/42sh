/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:01:52 by alallema          #+#    #+#             */
/*   Updated: 2017/02/05 17:13:36 by nbelouni         ###   ########.fr       */
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
	int			size;
	char		*to_paste;
	int			to_paste_size;
	char		*final_line;
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

t_prompt		manage_prompt(char *s, int num);
char			*get_prompt_str(void);
size_t			get_prompt_len(void);
void			set_prompt(char *s, int len);

size_t			calc_len(t_buf *buf, int x);
void			m_right(size_t len);
void			m_left(size_t len);
void			m_up(void);
void			m_down(t_buf *buf);
void			ft_del(size_t len);

int				vb_insert(t_buf *buf, char *s);
void			vb_del(t_buf *buf, unsigned int x);
int				vb_copy(t_buf *buf, unsigned int x);
int				vb_cut(t_buf *buf, unsigned int x);
int				vb_paste(t_buf *buf);

void			insert_in_buf(t_buf *buf, int cursor, char *s, size_t len);
void			delete_in_buf(t_buf *buf, int cursor, size_t len);
int				set_to_paste(t_buf *buf, int cursor, size_t len);
void			paste_in_buf(t_buf *buf, int cursor);

void			print_post_curs(t_buf *buf);

int				is_line_ended(t_buf *buf);

/*
** 	edition de ligne
*/
/*
**	affichage :
*/
/*
** ->>> history
*/
/*
** ->>> completion
*/

#endif
