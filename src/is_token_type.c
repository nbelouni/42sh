/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 19:27:07 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/08 13:24:47 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			is_separator_type(int type)
{
	if (type == DOT || type == PIPE || type == OR || type == AND)
		return (1);
	return (0);
}

int			is_open_group_type(int type)
{
	if (type == O_BRACKET || type == O_BRACE)
		return (1);
	return (0);
}

int			is_close_group_type(int type)
{
	if (type == C_BRACKET || type == C_BRACE)
		return (1);
	return (0);
}

int			is_dir_type(int type)
{
	if (type == SR_DIR || type == DL_DIR || type == DR_DIR ||
	type == DIR_AMP || type == SL_DIR)
		return (1);
	return (0);
}

int			is_text_type(int type)
{
	if (type == CMD || type == ARG || type == FD_IN || type == FD_OUT)
		return (1);
	return (0);
}
