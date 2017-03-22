/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/22 12:27:09 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	launch_job(t_job *j);
void	export_job(t_tree *root, List_p *job_list);
	void printJobList(List_p jobList);

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
	List_p	joblist = NULL;

	ast = NULL;
	list = NULL;
	env = NULL;
	env = ft_env_to_list(envp, env);
	if (init_completion(&completion, env) == ERR_EXIT)
		return (-1);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_curs();
	while ((ret_read = read_line(buf, &completion)) != ERR_EXIT)
	{
		close_termios();
//		init_shell();
		joblist = NULL;
		if (ret_read != TAB)
		{
			if (is_line_ended(buf) < 0)
				return (-1);
			complete_final_line(buf, list);
//			parse(env, buf->final_line, envp);
			ret = parse_buf(&list, buf->final_line, &completion);
			if (ret > 0 && list)
			{
				ft_print_token_list(&list); //debug impression
				ft_push_ast(list, &ast);
//				print_debug_ast(ast);
/*				PUT2("\ntest\n");
				char *av[1];

				av[0] = "ls";
				av[1] = NULL;
				execve(av[0], av, envp);
*///				test_func(ast);
				export_job(ast, &joblist);
				printJobList(joblist);
				list_iter(joblist, (void *)launch_job);
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
