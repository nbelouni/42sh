/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_local_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:40:34 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/15 23:57:30 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_token		*is_local_var(t_token *lst)
{
	t_token	*tmp;
	t_token	*new;
	int		n_tmp;
	int		lvl[2];
	char	*cmd;

	n_tmp = 0;
	tmp = lst;
	if (!ft_strchr(lst->word, '='))
		return (lst);
	while (tmp && ft_strchr(tmp->word, '='))
	{
		tmp = tmp->next;
		n_tmp++;
	}
	if (tmp && is_text_type(tmp->type))
		cmd = "env";
	else
		cmd = "export";
	lvl[0] = lst->bt_level;
	lvl[1] = lst->bc_level;
	if (!(new = ft_tokenew(CMD, ft_strdup(cmd), lvl)))		
		return (NULL);
	if (lst->prev)
		lst->prev->next = new;
	new->prev = lst->prev;
	lst->prev = new;
	new->next = lst;
	return (new);

}
