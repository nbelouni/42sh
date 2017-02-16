/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 20:44:31 by alallema          #+#    #+#             */
/*   Updated: 2017/02/16 22:20:09 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static char		*(tab_name[19]) = {
	[NO_TOKEN] = "NO_TOKEN",
	[CMD] = "CMD",
	[ESPACE] = "ESPACE",
	[O_BRACKET] = "O_BRACKET",
	[DOT] = "DOT",
	[PIPE] = "PIPE,",
	[START] = "START",
	[SL_DIR] = "SL_DIR",
	[SR_DIR] = "SR_DIR",
	[AMP] = "AMP",
	[OR] = "OR",
	[AND] = "AND",
	[DL_DIR] = "DL_DIR",
	[DR_DIR] = "DR_DIR",
	[DIR_AMP] = "DIR_AMP",
	[O_BRACE] = "O_BRACE",
	[C_BRACE] = "C_BRACE"
};

void		ft_print_token_list(t_token **list)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		PUT2("--LIST--\n");
		PUT2("token :");PUT2(elem->word);X('\n');
		PUT2("type :");PUT2(tab_name[elem->type]);X('\n');
		PUT2("bt_level :");E(elem->bt_level);X('\n');
		PUT2("bc_level :");E(elem->bc_level);X('\n');
		PUT2("____________\n");
		elem = elem->next;
	}
}
