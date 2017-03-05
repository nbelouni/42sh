/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/05 15:44:37 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	parse(t_lst *env, char *line, char **envp)
{
	char	**args;

	(void)envp;
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
		else
			ft_waitchild(args, envp);
		ft_tabdel(args);
	}
}

int		complete_final_line(t_buf *buf, t_token *lst)
{
	t_token	*tmp;
	char	*tmp2;

	if (!lst || !buf->line[0])
		return (0);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	if (is_backslash(tmp->word, strlen(tmp->word) - 1))
		return (0);
	if ((tmp->bt_level || tmp->bc_level) && !is_separator_type(tmp->type))
	{
		if (!(tmp2 = ft_strjoin(buf->final_line, "; ")))
			return(ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	}
	else
	{
		if (!(tmp2 = ft_strjoin(buf->final_line, " ")))
			return(ft_print_error("42sh: ", ERR_MALLOC, ERR_EXIT));
	}
	free(buf->final_line);
	buf->final_line = tmp2;
	return (0);
}

int 	main(int argc, char **argv, char **envp)
{

	(void)envp;
	(void)argc;
	(void)argv;

	t_completion	completion = {NULL, NULL, NULL, NULL};
	t_buf	*buf;
	t_token	*list;
	t_lst	*env;
	int		ret;
	int		ret_read;

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
		if (ret_read != TAB)
		{
			if (is_line_ended(buf) < 0)
				return (-1);
			ret = parse_buf(&list, buf->final_line);
//			if (ret > 0 && list)
//				ft_print_token_list(&list); //debug impression
			if (ret != ERR_NEW_PROMPT)
				ft_strdel(&(buf->final_line));
			else
				complete_final_line(buf, list);
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
