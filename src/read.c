/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:47:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/10 20:24:26 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "read.h"


int		cpy_cut_paste(t_buf *buf, int x)
{
	if (x == CTRL_F || x == CTRL_N || x == CTRL_A || x == CTRL_I)
	{
		if (vb_copy(buf, x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
		}
		return (1);
	}
	else if (x == CTRL_B || x == CTRL_E || x == CTRL_K || x == CTRL_W)
	{
		if (vb_cut(buf, x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
		}
		return (1);
	}
	else if (x == CTRL_P)
	{
		if (vb_paste(buf) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
		return (1);
	}

	return (0);
}

int		mv_and_read2(t_buf *buf, int x)
{
	int i;

	i = 0;
	if (x == DEL)
	{
		vb_del(buf, x);
		return (1);
	}
	else if (x == ALT_UP)
	{
		m_up();
		return (1);
	}
	else if (x == ALT_DOWN)
	{
		m_down(buf);
		return (1);
	}
	else if (x == LEFT || x == HOME || x == ALT_LEFT)
	{
		m_left(calc_len(buf, x));
		return (1);
	}
	else if (x == RIGHT || x == END || x == ALT_RIGHT)
	{
		m_right(calc_len(buf, x));
		return (1);
	}
	return (0);
}

// char 	*cut_bit(int x)
// {
// 	char *test;
// 	int i;
//
// 	test = ft_strnew(sizeof(int));
// 	i = 0;
// 	return (test);
// }

/*
**  TODO cut bite cree un chaine decouper a partire de int x
**	mais fuck va falloir une tampon ou une autre maniere de read
**	ou faire une copy de vbinsert avec l'utilistation d'une chaine
*/

int		mv_and_read(t_buf *buf, int x, int ret)
{
	int i;

	i = 0;
	if (ret < 0)
		return (ft_print_error("\n42sh", ERR_READ, ERR_EXIT));
	if (x == CTRL_D)
		return (ERR_EXIT);
	if (ft_isprint(x))
	{
		if (vb_insert(buf, (char *)&x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
		return (1);
	}
	else if (mv_and_read2(buf, x))
		return (1);
	return (0);
}

/*
**	Y faut trouver un autre moyen de recuperer les caracteres speciaux
**	TODO ; j'ai jsute modifier le read
*/

void	init_line(t_buf *buf)
{
	init_termios();
	ft_putstr_fd(get_prompt_str(), 1);
	print_pre_curs(buf);
	print_post_curs(buf);
}


int			vb_insert2(t_buf *buf, char s)
{
	int cursor;

	//ft_putendl("rentre dans vb_inse")
	cursor = g_curs.win_col * g_curs.row + g_curs.col;
	t_puts("im", 1);
	t_puts("ic", 1);
	//ft_putchar_fd(s, 1);
	if (buf->size + 1 >= BUFF_SIZE)
		return (-1);
	insert_in_buf(buf, cursor - get_prompt_len(), &s, 1);
	buf->size += 1;
	if (g_curs.col + 1 < g_curs.win_col)
		g_curs.col += 1;
	else
	{
		g_curs.col = 0;
		g_curs.row++;
		t_puts("cr", 1);
		t_puts("do", 1);
	}
	print_post_curs(buf);
	t_puts("ei", 1);
	return (0);
}

int testmv_and_read(t_buf *buf, int x)
{
	if (ft_isprint(x))
	{
		if (vb_insert2(buf, x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
		return (1);
	}
	return (0);
}

int 	catch_keys(t_buf *buf, int x, int ret, t_completion *cplt)
{
	int 	err;
//	char 	*tmp;
	char 	i;

	err = 0;
	i = 0;
	if ((err = mv_and_read(buf, x, ret)) < 0)
		return (err);
	else if (err != 1)
	{
		if ((err = cpy_cut_paste(buf, x)) < 0)
			return (err);
		else if (err != 1)
		{
			if ((err = complete_line(buf, cplt, x)) < 0)
				return (err);
			else if (err == 2)
			{
				while (x != 0)
				{
					i = x & 0xff;
					testmv_and_read(buf, i);
					x >>= 8;
					i++;
				}
//				PUT2("cut_bit ->>  ");
				//tmp = cut_bit(x);
				//PUT2(tmp);
	//			PUT2("\n");
				// while (i < 5)
				// {
				// 	mv_and_read(buf, tmp[i], ret);
				// 	tmp++;
				// 	i++;
				// }
			}
		}
	}
	return (err);
}

int		read_line(t_buf *buf, t_completion *cplt)
{
 	int				x;
	int				ret;
	int				err;

	x = 0;
	err = 0;
	init_line(buf);
	while ((ret = read(0, &x, sizeof(int))))
	{
		if (catch_keys (buf, x, ret, cplt) == ERR)
			return (ERR);
		if (x == RETR)
		{
			m_right(calc_len(buf, END));
			ft_putchar_fd((char)x, 1);
			return (0);
		}
		x = 0;
	}
	close_termios();
	return (END_EOT);
}
