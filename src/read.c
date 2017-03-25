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
	}
	if (x == CTRL_B || x == CTRL_E || x == CTRL_K || x == CTRL_W)
	{
		if (vb_cut(buf, x) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_MALLOC, ERR_EXIT));
		}
	}
	if (x == CTRL_P)
	{
		if (vb_paste(buf) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
	}
	return (0);
}

int		mv_and_read2(t_buf *buf, int x)
{
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
		PUT2("fuck");
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

char 	*cut_bit(int x)
{
	char *test;
	int i;

	test = ft_strnew(sizeof(int));
	i = 0;
	while (x != 0)
	{
		test[i] = x & 0xff;
		x >>= 8;
		i++;
	}
	ft_putstr(test);
	return (test);
}

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
	}
	else if (mv_and_read2(buf, x) == 0)
	{
		if (vb_insert(buf, cut_bit(x)) < 0)
		{
			m_right(calc_len(buf, END));
			return (ft_print_error("\n42sh", ERR_CMD_TOO_LONG, ERR_NEW_CMD));
		}
	}
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

int		read_line(t_buf *buf, t_completion *cplt)
{
 	int				x;
	int				ret;
	int				err;
	int				i;

	i = -1;
	x = 0;
	err = 0;
	init_line(buf);
	while ((ret = read(0, &x, sizeof(int))))
	{
		if ((err = mv_and_read(buf, x, ret)) < 0 ||
		(err = cpy_cut_paste(buf, x)) < 0 ||
		(err = complete_line(buf, cplt, x)) != 0)
			return (err);
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
