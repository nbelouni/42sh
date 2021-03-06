/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/06 20:51:20 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

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
		if ((ret = parse_builtins(core, args[0], args + 1)) == 1)
			ft_waitchild(args, envp);
		ft_tabdel(args);
	}
	if ((ft_check_history_var(core->set, core->hist)) == ERR_EXIT)
		return (ERR_EXIT);
	return (0);
}


/*
 **	  init_core initialisation des liste d'env
 */

t_core 		*ft_creat_core(char **envp)
{
	t_core *core;

	core = ft_init_core();
	core->set = ft_init_lstset();
	core->exp = ft_init_list();
	if (envp != NULL && envp[0] != NULL)
		core->env = ft_env_to_list(envp, core->env);
	else
		core->env = ft_default_env();
	ft_histopt_r(&(core->hist), core->set, NULL);
	return (core);
}

/*
 **   si l'entree est different du terminal va lire ligne par ligne GNL
 */
int 	read_ext(t_buf *buf, t_completion *comp, t_core *core, t_token *list)
{
	int i;
	char *line = NULL;

	i = 0;
	if (buf->istty == 1)
	{
		while (get_next_line(0, &line) > 0)
		{
			buf->final_line = line;
			PUT2(buf->final_line);
			parse_buf(&list, buf->final_line, comp, core->hist);
			PUT2("\n line "); E(i);
			ft_print_token_list(&list);
			++i;
		}
		return (0);
	}
	return (1);
}

int 	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_completion	completion = {NULL, NULL, NULL, NULL};
	t_buf	*buf;
	t_token	*list;
	int		ret;
	int		ret_read;
	t_tree	*ast;
	t_core	*core;

	ast = NULL;
	list = NULL;
	core = ft_creat_core(envp);
	if (init_completion(&completion, core) == ERR_EXIT)
		return (-1);
	signal(SIGWINCH, get_sigwinch);
	signal(SIGINT, get_sigint);
	if (!(buf = init_buf()))
		return (ft_print_error("42sh", ERR_MALLOC, ERR_EXIT));
	if (!isatty(0))
		buf->istty = 1;
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	if (read_ext(buf, &completion, core, list) == 1)
	{
		init_curs();
		while ((ret_read = read_line(buf, &completion, core->hist)) != ERR_EXIT)
		{
			close_termios();
			if (ret_read != TAB)
			{
				if (is_line_ended(buf) < 0)
					return (-1);
				bang_substitution(&(buf->final_line), core);
				ret = parse_buf(&list, buf->final_line, &completion, core->hist);
				if (ret > 0 && list)
				{
					parse(core, buf->final_line, envp);
					/*
					 **			ft_push_ast(list, &ast);
					 **				. remplace $var
					 **				. ajoute arguments si regex
					 **				. supprime '\'', '"' , '`' et '\\'
					 **
					 **				. sera remplacee quqnd je saurais ou la mettre
					 **				regexp_in_tree(ast, core);
					 **
					 */
					//			print_debug_ast(ast);
					//			free_ast(ast);

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
	}
	free_buf(buf);
	return (0);
}
