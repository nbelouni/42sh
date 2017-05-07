/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/07 19:17:37 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	launch_job(t_job *j);
void	export_job(t_tree *root, t_list **job_list);
void	printJobList(t_list *job_list);

t_job	*last_job = NULL;

t_list	*g_job_list = NULL;
t_core	*g_core = NULL;
t_bool	g_is_here_doc;

static t_builtin_array g_builtin_array[] =
{
	{"cd", &ft_builtin_cd},
	{"env", &ft_builtin_env},
	{"setenv", &ft_builtin_setenv},
	{"unsetenv", &ft_builtin_unsetenv},
	{"exit", &ft_builtin_exit},
	{"echo", &ft_builtin_echo},
	{"history", &ft_builtin_history},
	{"unset", &ft_builtin_unset},
	{"export", &ft_builtin_export},
	{"jobs", &ft_builtin_jobs},
	{"fg", &ft_builtin_fg},
	{"bg", &ft_builtin_bg},
	{NULL, NULL}
};

int		parse_builtins(t_core *core, char *cmd, char **cmd_args)
{
	int	i;

	i = -1;

	while (g_builtin_array[++i].cmd)
	{
		if (cmd)
		{
			if (ft_strncmp(g_builtin_array[i].cmd, cmd, ft_strlen(cmd)) == 0)
				return (g_builtin_array[i].func(core, cmd_args));
		}
	}
	return (1);
}

static int	pre_core(t_buf **buf, t_completion *completion, char **envp)
{
//`	struct termios termio;

	g_is_here_doc = FALSE;
//	tcgetattr(0, &termio);
	if (ft_creat_core(envp) == ERR_EXIT)
		return (ERR_EXIT);
	if (!(*buf = init_buf()))
		return (ft_print_error("21sh", ERR_MALLOC, ERR_EXIT));
	if (init_completion(completion, g_core) == ERR_EXIT)
		return (-1);
	if (!isatty(0))
		return (ft_print_error("21sh", " : Input not from a tty", ERR_NEW_CMD));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_shell();
	g_core->buf = *buf;
	signal(SIGWINCH, get_sigwinch);
	g_curs.win_row = 0;
	g_curs.win_col = 0;
	g_curs.row = 0;
	g_curs.col = 0;
	init_curs();
	return (0);
}

int 	main(int argc, char **argv, char **envp)
{
	(void)argc;
  	(void)argv;
	t_completion	completion;
	t_buf	*buf;
	t_token	*list;
	int		ret;
	int		ret_read;
	t_tree	*ast;
	t_list	*job_list_bis = NULL;

	(void)argc;
	(void)argv;
	completion = (t_completion){NULL, NULL, NULL, NULL};
	buf = NULL;
	if ((ret = pre_core(&buf, &completion, envp)) < 0)
		return (ret);
	while ((ret_read = read_line(g_core->buf, &completion, g_core->hist)) != ERR_EXIT)
	{
		close_termios();
		job_list_bis = NULL;
		if (ret_read != TAB && ret_read != ERR_NEW_CMD)
		{
			list = NULL;
			int	ret_subs = 0;
			if (is_line_ended(g_core->buf) < 0)
				return (-1);
			ret_subs = bang_substitution(&(g_core->buf->final_line), g_core);
			if ((ft_cmd_to_history(g_core->hist, g_core->buf->final_line)) == ERR_EXIT)
				return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
			ret = parse_buf(&list, g_core->buf->final_line, &completion, g_core->hist);
			if (ret > 0 && list && ret_subs == 0)
			{
				job_list_bis = NULL;
				ast = NULL;
				if ((ret = ft_check_history_var(g_core)) == ERR_EXIT)
				{
					return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
				}
				ft_push_ast(list, &ast);
				export_job(ast, &job_list_bis);
				list_iter(job_list_bis, (void *)launch_job);
				delete_list(&job_list_bis, NULL);
				free_ast(ast);
			}
			else if (ret_subs == 2)
				ft_putendl(g_core->buf->final_line);
			if (ret != ERR_NEW_PROMPT && g_core->buf->final_line)
				ft_strdel(&(g_core->buf->final_line));
			else
				complete_final_line(g_core->buf, list);
			if (list)
				ft_tokendestroy(&list); //clean la list a mettre a la fin
			ft_bzero(g_core->buf->line, BUFF_SIZE);
			g_core->buf->size = 0;
			clean_pos_curs();
			if (init_completion(&completion, g_core) == ERR_EXIT)
				return (-1);
		}
		if (ret_read == END_EOT)
			break ;
	}
	close_termios();
	free_buf(g_core->buf);
	return (0);
}
