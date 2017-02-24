/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/24 17:22:13 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	parse(t_lst *env, char *line, char **envp)
{
	char	**args;

	(void)envp;
	args = NULL;
	args = ft_strsplit(line, ' ');
	if (args && args[0])
	{
		if (ft_strcmp(args[0], "exit") == 0)
			ft_builtin_exit(env, args[0], args + 1);
		else if (ft_strcmp(args[0], "env") == 0)
			ft_builtin_env(env, args[0], &args[1]);
		else if (ft_strcmp(args[0], "setenv") == 0)
			ft_builtin_setenv(env, args[0], args + 1);
		else if (ft_strcmp(args[0], "unsetenv") == 0)
			ft_builtin_unsetenv(env, args[0], &args[1]);
		else if (ft_strcmp(args[0], "echo") == 0)
			ft_builtin_echo(env, args[0], args + 1);
		else if (ft_strcmp(args[0], "cd") == 0)
			ft_builtin_cd(env, args[0], args + 1);
		else
			ft_waitchild(args, envp);
		ft_tabdel(args);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_buf	*buf;
	t_token	*list;
	t_lst	*env;
	int		ret;
	int		ret_read;

	env = NULL;
	env = ft_env_to_list(envp, env);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_curs();
	while ((ret_read = read_line(buf)) != ERR_EXIT)
	{
		close_termios();
		if (is_line_ended(buf) < 0)
			return (-1);
		ret = parse_buf(&list, buf->final_line);
/*
**	DECOMMENTER POUR AFFICHER LA LISTE
*/
//		if (ret > 0)
//			ft_print_token_list(&list); //debug impression
		if (ret != ERR_NEW_PROMPT)
			ft_strdel(&(buf->final_line));
		if (list)
			ft_tokendestroy(&list); //clean la list a mettre a la fin
		ft_bzero(buf->line, BUFF_SIZE);
		buf->size = 0;
		clean_pos_curs();
		if (ret_read == END_EOT)
			break ;
	}
	close_termios();
	free_buf(buf);
	return (0);
}
