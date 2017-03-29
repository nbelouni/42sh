/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/29 14:48:47 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	launch_job(t_job *j);
void	export_job(t_tree *root, List_p *job_list);
void	printJobList(List_p jobList);

List_p	jobList = NULL;

int		parse(t_core *set, char *line, char **envp)
{
	char	**args;

	(void)envp;
	if ((ft_cmd_to_history(set->hist, line)) == ERR_EXIT)
		return (ERR_EXIT);
	args = NULL;
	args = ft_strsplit(line, ' ');
	if (args != NULL && args[0] != NULL)
	{
		if (ft_strcmp(args[0], "exit") == 0)
			ft_builtin_exit(set, args[0], args + 1);
		else if (ft_strcmp(args[0], "env") == 0)
			ft_builtin_env(set->env, &args[1]);
		else if (ft_strcmp(args[0], "setenv") == 0)
			ft_builtin_setenv(set->env, args[0], args + 1);
		else if (ft_strcmp(args[0], "unsetenv") == 0)
			ft_builtin_unsetenv(set->env, args[0], &args[1]);
		else if (ft_strcmp(args[0], "echo") == 0)
			ft_builtin_echo(set->env, args[0], args + 1);
		else if (ft_strcmp(args[0], "cd") == 0)
			ft_builtin_cd(set->env, args[0], args + 1);
		else if (ft_strcmp(args[0], "export") == 0)
			ft_builtin_export(args, set);
		else if (ft_strcmp(args[0], "unset") == 0)
			ft_builtin_unset(set, args);
		else if (ft_strcmp(args[0], "history") == 0)
			ft_builtin_history(set->set, set->hist, args + 1);
		else if (ft_strcmp(args[0], "set") == 0)
			ft_print_lst(set->set);
//		else
//			ft_waitchild(args, envp);
		ft_tabdel(args);
		args = NULL;
	}
	if ((ft_check_history_var(set->set, set->hist)) == ERR_EXIT)
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
//	t_core	*set;

	ast = NULL;
	list = NULL;
	set = ft_init_set();
	set->env = NULL;
	set->set = ft_init_lstset();
	set->hist = NULL;
	ft_histopt_r(&(set->hist), set->set, NULL);
	if (envp != NULL && envp[0] != NULL)
		set->env = ft_env_to_list(envp, set->env);
	if (init_completion(&completion, set->env) == ERR_EXIT)
		return (-1);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_curs();
	init_shell();
	while ((ret_read = read_line(buf, &completion)) != ERR_EXIT)
	{
		close_termios();
		jobListBis = NULL;
		if (ret_read != TAB)
		{
			if (is_line_ended(buf) < 0)
				return (-1);
			complete_final_line(buf, list);
			//parse(set, buf->final_line, envp);
			ret = parse_buf(&list, buf->final_line, &completion);
//			parse(set, buf->final_line, envp);
			if (ret > 0 && list)
			{
//				ft_print_token_list(&list); //debug impression
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
			}
			if (ret != ERR_NEW_PROMPT)
				ft_strdel(&(buf->final_line));
			if (list)
				ft_tokendestroy(&list); //clean la list a mettre a la fin
			ft_bzero(buf->line, BUFF_SIZE);
			buf->size = 0;
			clean_pos_curs();
		}
		if (ret_read == END_EOT)
			break ;
	}
	close_termios();
	free_buf(buf);
	return (0);
}
