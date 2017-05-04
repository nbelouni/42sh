/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/05/04 18:08:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_core	*g_core;

t_bool		get_win(void)
{
	struct winsize	windows;
	int				len;

	len = get_curs_add(-(get_prompt_len()));
	if (ioctl(0, TIOCGWINSZ, &windows) < 0)
		return (FALSE);
	if ((g_curs.win_col * g_curs.row) + g_curs.col >= (int)get_prompt_len())
	{
		t_puts("cl", 1);
		ft_putstr_fd(get_prompt_str(), 1);
	}
	g_curs.win_col = windows.ws_col;
	g_curs.win_row = windows.ws_row;
	clean_pos_curs();
	print_post_curs(g_core->buf);
	m_right(len);
	return (TRUE);
}

void		get_sigwinch(int sig)
{
	if (sig == SIGWINCH)
		get_win();
	return ;
}

void		update_status(void);

void		sigchld_handler(int sigchld)
{
	(void)sigchld;
	update_status();
//	do_job_notification();
}

void		get_sigint(int sig)
{
	int status;
	int pid;

	pid = waitpid(-1, &status, WUNTRACED);
	if (sig == SIGINT)
	{
		m_right(calc_len(g_core->buf, END));
		g_core->buf->size = 0;
		ft_bzero(g_core->buf->line, BUFF_SIZE);
		ft_strdel(&(g_core->buf->final_line));
		set_prompt(PROMPT1, ft_strlen(PROMPT1));
		clean_pos_curs();
		ft_putchar('\n');
	}
	return ;
}

void		init_signal(void)
{
	struct sigaction act;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_flags = 0;
	act.sa_handler = &get_sigint;
	sigaction(SIGINT, &act, NULL);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
