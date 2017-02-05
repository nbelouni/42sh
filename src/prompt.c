/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 16:29:50 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/05 16:38:15 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

t_prompt	manage_prompt(char *s, int num)
{
	static t_prompt	prompt;

	if (s)
		prompt.s = s;
	if (num)
		prompt.len = num;
	return (prompt);
}

char		*get_prompt_str(void)
{
	return (manage_prompt(NULL, 0).s);
}

void		set_prompt(char *s, int len)
{
	manage_prompt(s, len);
}

size_t		get_prompt_len(void)
{
	return ((size_t)manage_prompt(NULL, 0).len);
}
