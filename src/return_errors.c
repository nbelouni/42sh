/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 17:03:05 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/01 21:46:08 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		return_new_prompt(int ret)
{
	if (ret == ERR_EXIT)
		return (ret);
	else if (ret == ERR_NEW_PROMPT)
	{
		set_prompt(PROMPT2, ft_strlen(PROMPT2));
		return (ERR_NEW_PROMPT);
	}
	return (ret);
}

int		free_rg_and_return(char **rg, int ret)
{
	if (rg && rg[0])
	{
		ft_bzero(*rg, ft_strlen(*rg));
		ft_strdel(rg);
	}
	return (ret);
}
