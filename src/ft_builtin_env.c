/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:24:17 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/13 17:52:43 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	ft_lstdup cree une copie d'une liste et la retourne.
*/

t_lst		*ft_lstdup(t_lst *to_dup)
{
	t_lst	*dup_lst;
	t_elem	*tmp;
	t_elem	*tmp2;

	tmp = to_dup->head;
	if ((dup_lst = ft_init_list()) == NULL)
		return (NULL);
	tmp2 = dup_lst->head;
	while (tmp != NULL)
	{
		if ((tmp2 = ft_init_elem()) == NULL)
			return (NULL);
		tmp2->name = ft_strdup(tmp->name);
		tmp2->value = (tmp->value) ? ft_strdup(tmp->value) : NULL;
		ft_add_elem(tmp2, dup_lst);
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	return (dup_lst);
}

/*
**	ft_parse_env va parser les arguments par rapport a un index i
**	et renvoyer ce meme index, incrémenté ou non. Si les arguments
**	possedent un caractere '=' et qu'il n'est pas en premiere position,
**	la chaine est considéré comme valide et on appelle notre ft_setenv
**	afin de l'ajouter sous forme de maillon dans la liste d'env temporaire.
*/

static int	ft_parse_env(t_lst **lst, char **args, int i)
{
	char	*name;
	char	*value;

	if (!(*lst) && ft_strchr(args[i], '=') && args[i][0] != '=')
	{
		if (((*lst) = ft_init_list()) == NULL)
			return (ERR_EXIT);
	}
	while (args[i] != NULL)
	{
		if (!ft_strchr(args[i], '='))
			break ;
		if (args[i][0] == '=')
			return (ft_print_error(args[i], ERR_ARG_INVALID, ERR_NEW_CMD));
		value = NULL;
		name = ft_strsub(args[i], 0, ft_get_index_of(args[i], '='));
		if (ft_strlen(name) < ft_strlen(args[i]) + 1)
			value = ft_strdup(args[i] + ft_strlen(name) + 1);
		if (ft_setenv((*lst), name, value) == ERR_EXIT)
			return (ERR_EXIT);
		(value) ? ft_multi_free(name, value, NULL, NULL) : ft_strdel(&name);
		i++;
	}
	return (i);
}

/*
**	ft_builtin_env est le builtin gerant la commande "env" de notre shell,
**	elle affiche la liste d'environnement si aucun parametre ne lui est passé
**	ou fait du traitement sur un dup de cette liste si des arguments
**	autres que l'option -i lui sont passé.
*/

int			ft_builtin_env(t_lst *env, char *cmd, char **args)
{
	int		*opt;
	t_lst	*dup_env;

	opt = NULL;
	dup_env = NULL;
	(void)cmd;
	if ((!args || !args[0]))
		(env && env->head) ? ft_print_lst(env) : 0;
	else
	{
		opt = ft_opt_parse(opt, ENV_OPT, args, 0);
		if (opt == (int *)-1 || opt == (int *)-2)
			return ((int)opt);
		if (env && (opt && !opt[0]))
		{
			if ((dup_env = ft_lstdup(env)) == NULL)
				return (ERR_EXIT);
		}
		if ((opt[0] = ft_parse_env(&dup_env, args, opt[0])) != -1)
			(args[opt[0]]) ? ft_putendl("bin func") : ft_print_lst(dup_env);
		(dup_env) ? ft_del_list(dup_env) : NULL;
		free(opt);
	}
	return ((opt && opt == (int *)-1) ? -1 : 0);
}
