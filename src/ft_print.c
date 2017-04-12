/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 20:44:31 by alallema          #+#    #+#             */
/*   Updated: 2017/03/27 17:51:57 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
 * fonction de debug pour affichage de la liste chainee
 **/

static char		*(tab_name[23]) = {
	[NO_TOKEN] = "NO_TOKEN",
	[CMD] = "CMD",
	[ESPACE] = "ESPACE",
	[O_BRACKET] = "O_BRACKET",
	[C_BRACKET] = "C_BRACKET",
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
	[LR_DIR] = "LR_DIR",
	[DIR_L_AMP] = "DIR_L_AMP",
	[DIR_R_AMP] = "DIR_R_AMP",
	[O_BRACE] = "O_BRACE",
	[C_BRACE] = "C_BRACE",
	[FD_IN] = "FD_IN",
	[TARGET] = "TARGET",
	[ARG] = "ARG"
};

void		ft_print_token_list(t_token **list)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		PUT2("--LIST--\n");
		if (elem->word)
			PUT2("token :");PUT2(elem->word);X('\n');
		PUT2("type :");PUT2(tab_name[elem->type]);X('\n');
		PUT2("bt_level :");E(elem->bt_level);X('\n');
		PUT2("bc_level :");E(elem->bc_level);X('\n');
		PUT2("____________\n");
		elem = elem->next;
	}
	
// 	elem = *list;
//	PUT2("\n______PREV______\n");
//	while (elem && elem->next)
//		elem = elem->next;
//	while (elem)
//	{
//		PUT2("--LIST--\n");
//		PUT2("token :");PUT2(elem->word);X('\n');
//		PUT2("type :");PUT2(tab_name[elem->type]);X('\n');
//		PUT2("bt_level :");E(elem->bt_level);X('\n');
//		PUT2("bc_level :");E(elem->bc_level);X('\n');
//		PUT2("____________\n");
//		elem = elem->prev;
//	}

}
/*
void		print_job(t_job *list)
{
	t_job		*job;
	t_process	*process;
	int			i;
	int			j;

	i = 1;
	j = 1;
	job = list;
	process = NULL;
	job = list;
	while (job)
	{
		process = job->process;
		PUT2("\n--- job");
		E(i);
		PUT2("--\n");
		while (process)
		{
			PUT2("\n--- process ");
			E(j);
			PUT2(process->cmd[0]);
			PUT2("--\n");
			process = process->next;
			j++;
		}
		i++;
		job = job->next;
	}
}*/
