/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 18:33:02 by alallema          #+#    #+#             */
/*   Updated: 2017/05/05 18:54:28 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
#include "io.h"
#include "job.h"

int			list_int2(t_list *list, int (*f)(void *, int, int), int d, int t)
{
	int		ret;

	while (list)
	{
		if ((ret = f(list->content, d, t)))
			return (ret);
		list = list->next;
	}
	return (0);
}

static int	return_or_exit(char *error, int dofork)
{
	if (dofork)
		exit(ft_print_error("21sh", error, ERR_EXIT));
	return (1);
}

int			redir_open(t_io *io, int dofork)
{
	struct stat	stat;

	lstat(io->str, &stat);
	if (S_ISDIR(stat.st_mode))
	{
		return (ft_print_error("21sh", ERR_IS_DIR,
			return_or_exit(ERR_IS_DIR, dofork)));
	}
	if (io->flag & CLOSE && access(io->str, X_OK) == -1)
		io->dup_src = open(io->str, io->mode, DEF_FILE);
	if (access(io->str, 0) == 0 && access(io->str, R_OK | W_OK) == -1)
	{
		return (ft_print_error("21sh", ERR_NO_ACCESS,
			return_or_exit(ERR_NO_ACCESS, dofork)));
	}
	if (io->dup_src < 0)
	{
		return (ft_print_error("21sh", ERR_NO_FILE,
			return_or_exit(ERR_NO_FILE, dofork)));
	}
	return (0);
}

static int	check_close_fd(t_io *io, int dofork)
{
	if (io->dup_src > 2)
		close(io->dup_src);
	if (io->dup_target > 2)
		close(io->dup_target);
	if (io->tab_fd[0] > 2)
		close(io->tab_fd[0]);
	if (io->tab_fd[1] > 2)
		close(io->tab_fd[1]);
	return (ft_print_error("21sh", ERR_BADF,
		return_or_exit(ERR_BADF, dofork)));
}

int			apply_redir(t_io *io, int dofork)
{
	int		pipefd[2];
	int		ret;

	if (io->flag & OPEN)
	{
		if ((ret = redir_open(io, dofork)))
			return (ret);
	}
	if (io->flag & WRITE && pipe(pipefd) != -1)
	{
		io->dup_src = pipefd[0];
		write(pipefd[1], io->str, ft_strlen(io->str));
		close(pipefd[1]);
	}
//	save_fd(io, token, dofork);
	if (io->flag & DUP)
	{
		if ((io->tab_fd[0] == io->dup_src)
				|| (dup2(io->dup_src, io->dup_target) == -1 && dofork))
			return (check_close_fd(io, dofork));
	}
	if (io->flag & CLOSE && io->flag ^ WRITE && io->dup_target != io->dup_src)
	{
		close(io->dup_src);
	}
	return (0);
}
