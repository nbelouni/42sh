/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/03 16:16:30 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	launch_job(t_job *j);
void	export_job(t_tree *root, List_p *job_list);
void	printJobList(List_p jobList);

List_p	jobList = NULL;

static t_builtin_array builtin_array[] =
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
	// {"jobs", &ft_builtin_jobs},
	// {"fg", &ft_builtin_fg},
	// {"bg", &ft_builtin_bg},
	{NULL, NULL}
};

int		parse_builtins(t_core *core, char *cmd, char **cmd_args)
{
	int	i;

	i = -1;
	while (builtin_array[++i].cmd)
	{
		if (ft_strcmp(builtin_array[i].cmd, cmd) == 0)
			return (builtin_array[i].func(core, cmd_args));
	}
	return (1);
}

int		parse(t_core *core, char *line, char **envp)
{
	char	**args;
	int		ret;

	(void)envp;
	ret = 0;
	if ((ft_cmd_to_history(core->hist, line)) == ERR_EXIT)
		return (ERR_EXIT);
	args = NULL;
	args = ft_strsplit(line, ' ');
	if (args != NULL && args[0] != NULL)
	{
//		if ((ret = parse_builtins(core, args[0], args + 1)) == 1)
//			ft_waitchild(args, envp);
		ft_tabdel(args);
	}
	if ((ft_check_history_var(core->set, core->hist)) == ERR_EXIT)
		return (ERR_EXIT);
	return (0);
}

int 	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_completion	completion = {NULL, NULL, NULL, NULL};
	t_buf	*buf;
	t_token	*list;
//	t_lst	*env;
	int		ret;
	int		ret_read;
	t_tree	*ast;
	List_p	jobListBis = NULL;
	t_core	*core;

	ast = NULL;
	list = NULL;
	core = ft_init_core();
	core->env = NULL;
	core->set = ft_init_lstset();
	core->hist = NULL;
	ft_histopt_r(&(core->hist), core->set, NULL);
	if (envp != NULL && envp[0] != NULL)
		core->env = ft_env_to_list(envp, core->env);
	if (init_completion(&completion, core) == ERR_EXIT)
		return (-1);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_curs();
	init_shell();
	while ((ret_read = read_line(buf, &completion, core->hist)) != ERR_EXIT)
	{
		close_termios();
		jobListBis = NULL;
		if (ret_read != TAB)
		{
			if (is_line_ended(buf) < 0)
				return (-1);
			bang_substitution(&(buf->final_line), core);
			// PUT2("2 buf->final_line : ");PUT2(buf->final_line);X('\n');
			ret = parse_buf(&list, buf->final_line, &completion, core->hist);
			if (ret > 0 && list)
			{

	//			ft_push_ast(list, &ast);

/*
 *				enleve les quotes et les backslash -> va changer de place
 *				edit_cmd(list, env);
 */
				ft_push_ast(list, &ast);
//				print_debug_ast(ast);
/*				PUT2("\ntest\n");
				char *av[1];

				av[0] = "ls";
				av[1] = NULL;
				execve(av[0], av, envp);
*///				test_func(ast);
				export_job(ast, &jobListBis);
//				printJobList(jobListBis);
				list_iter(jobListBis, (void *)launch_job);
				delete_list(&jobListBis, NULL);
				free_ast(ast);
//				free(ast);
/*
**				. remplace $var
**				. ajoute arguments si regex
**				. supprime '\'', '"' , '`' et '\\'
**
**				. sera remplacee quqnd je saurais ou la mettre
**				regexp_in_tree(ast, core);
**
*/

			}
			if (ret != ERR_NEW_PROMPT)
				ft_strdel(&(buf->final_line));
			else
				complete_final_line(buf, list);
			if (list)
				ft_tokendestroy(&list); //clean la list a mettre a la fin
			ft_bzero(buf->line, BUFF_SIZE);
			buf->size = 0;
			clean_pos_curs();
			if (init_completion(&completion, core) == ERR_EXIT)
				return (-1);
		}
		if (ret_read == END_EOT)
			break ;
	}
	close_termios();
	free_buf(buf);
	return (0);
}
