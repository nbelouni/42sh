/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 20:30:33 by alallema          #+#    #+#             */
/*   Updated: 2017/02/05 14:42:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "read.h"

int			t_putchar(int i)
{
	write(1, &i, 1);
	return (0);
}

void		t_puts(char *s, int i)
{
	tputs(tgetstr(s, NULL), i, t_putchar);
}

t_term		*get_term(void)
{
	static t_term	term;

	return (&term);
}

int			init_termios(void)
{
	t_term			*st_term;

	st_term = get_term();
	if (tgetent(NULL, getenv("TERM")) < 1)
		return (-1);
	if (tcgetattr(0, &st_term->old) == -1)
		return (-1);
	if (tcgetattr(0, &st_term->new) == -1)
		return (-1);
	st_term->new.c_lflag &= ~(ICANON | ECHO);
	st_term->new.c_cc[VMIN] = 1;
	st_term->new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &st_term->new) == -1)
		return (-1);
	return (0);
}

int			close_termios(void)
{
	t_term			*st_term;

	st_term = get_term();
	if (tcsetattr(0, TCSANOW, &st_term->old) == -1)
		return (-1);
	return (0);
}
