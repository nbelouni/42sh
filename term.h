/*struct term */

typedef struct	s_win
{
	int				col;
	int				row;
	int				letter;
	int				qt;
}				t_win;

typedef struct	s_term
{
	struct termios	old;
	struct termios	new;
}				t_term;

/*define read */

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

