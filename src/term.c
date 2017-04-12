/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 20:30:33 by alallema          #+#    #+#             */
/*   Updated: 2017/04/12 04:16:13 by llaffile         ###   ########.fr       */
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

	dprintf(2, "in -- %s\n", __func__);
	st_term = get_term();
	if (!getenv("TERM"))
		tgetent(NULL, "xterm-256color");
	else if (tgetent(NULL, getenv("TERM")) < 1)
		return (-1);
	if (tcgetattr(0, &st_term->old) == -1)
		return (-1);
	if (tcgetattr(0, &st_term->new) == -1)
		return (-1);
	if (st_term->new.c_lflag & TOSTOP)
		dprintf(2, "%s Dam it's there\n", __func__);
	st_term->new.c_lflag &= ~(ICANON | ECHO | TOSTOP);
	st_term->new.c_cc[VMIN] = 1;
	st_term->new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &st_term->new) == -1)
		return (-1);
	dprintf(2, "out -- %s\n", __func__);	
	return (0);
}

int			investigate(char *func);

int			close_termios(void)
{
	t_term			*st_term;
	sigset_t	set,oset;

	block_signal(SIGTTOU, &set, &oset);
	dprintf(2, "in -- %s\n", __func__);
	investigate((char *)__func__);
	st_term = get_term();
	st_term->old.c_lflag &= ~TOSTOP;
	if (tcsetattr(0, TCSADRAIN, &st_term->old) == -1)
		return (perror(__func__), -1);
	dprintf(2, "out -- %s\n", __func__);
	investigate((char *)__func__);
	unblock_signal(&oset);
	return (0);
}
