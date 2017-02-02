/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:25:06 by alallema          #+#    #+#             */
/*   Updated: 2017/02/02 22:21:10 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		clean_pos_curs(void)
{
	g_curs->col = PROMPT_LEN;
	g_curs->row = 0;
}

t_bool		init_curs(void)
{
	if (!(g_curs = ft_memalloc(sizeof(t_curs))))
		return (FALSE);
	if (get_win() == FALSE)
		return (FALSE);
	clean_pos_curs();
	return (TRUE);
}

void		destroy_curs(void)
{
	free(g_curs);
	g_curs = NULL;
}
