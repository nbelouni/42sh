/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/20 18:30:24 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	parse(t_set *m_env, char *line, char **envp)
{
	char	**args;
	t_lst *env;

	(void)envp;
	env = m_env->env;
	args = NULL;
	args = ft_strsplit(line, ' ');
	if (args != NULL && args[0] != NULL)
	{
		if (ft_strcmp(args[0], "exit") == 0)
			ft_builtin_exit(env, args[0], args + 1);
		else if (ft_strcmp(args[0], "env") == 0)
			ft_builtin_env(env, &args[1]);
		else if (ft_strcmp(args[0], "setenv") == 0)
			ft_builtin_setenv(env, args[0], args + 1);
		else if (ft_strcmp(args[0], "unsetenv") == 0)
			ft_builtin_unsetenv(env, args[0], &args[1]);
		else if (ft_strcmp(args[0], "echo") == 0)
			ft_builtin_echo(env, args[0], args + 1);
		else if (ft_strcmp(args[0], "cd") == 0)
			ft_builtin_cd(env, args[0], args + 1);
		else if (ft_strcmp(args[0], "export") == 0)
			ft_builtin_export(args, m_env);
		else if (ft_strcmp(args[0], "unset") == 0)
			ft_builtin_unset(m_env, args);
		else
			ft_waitchild(args, envp);
		ft_tabdel(args);
	}
}

int 	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_completion	completion = {NULL, NULL, NULL, NULL};
	t_buf	*buf;
	t_token	*list;
	t_lst	*env;
	t_set *multi_var_env;
	int		ret;
	int		ret_read;
	t_tree	*ast;

	ast = NULL;
	list = NULL;
	env = NULL;
	multi_var_env = ft_init_set();
	env = ft_env_to_list(envp, env);
	multi_var_env->env = env;
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
		if (ret_read != TAB)
		{
			if (is_line_ended(buf) < 0)
				return (-1);
			complete_final_line(buf, list);
//			parse(multi_var_env, buf->final_line, envp);
			ret = parse_buf(&list, buf->final_line, &completion);
			if (ret > 0 && list)
			{

				ft_print_token_list(&list); //debug impression
				
//				enleve les quotes et les backslash -> va changer de place
				edit_cmd(list, env); 

//				ft_push_ast(list, &ast);
//				print_debug_ast(ast);
//				free_ast(ast);
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
