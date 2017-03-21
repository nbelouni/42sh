/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:21:52 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/20 15:07:17 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	la fonction ft_builtin_exit gere les erreurs des arguments (s'il y en a),
**	retourne -1 comme tout builtin si une erreur occure, sinon exit est appelé
**	soit avec 0 (si aucun arguments n'est présent), ou la valeur numeric
**	contenu dans args[0] (plus d'arguments provoque une erreur).
*/

int		ft_builtin_exit(t_core *core, char *cmd, char **args)
{
	int	ret;

	ret = 0;
	if (args && args[0])
	{
		if (!ft_isdigit(args[0][0]) || args[1])
		{
			return (ft_print_error(cmd, ERR_EXPR_SYNT, ERR_NEW_CMD));
		}
		else if (!ft_strisdigit(args[0]) && args[0][0] != '-')
		{
			return (ft_print_error(cmd, ERR_EXT_FRMT, ERR_NEW_CMD));
		}
		ret = (unsigned char)ret;
		ret = ft_atoi(args[0]);
	}
	ft_histopt_w(core->set, core->hist, NULL);
	ft_del_list(core->env);
	clean_pos_curs();
	close_termios();
	exit(ret);
	return (ret);
}
