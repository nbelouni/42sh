/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:26:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/15 20:41:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_word	*create_word(void)
{
	t_word	*elem;

	if (!(elem = ft_memalloc(sizeof(t_word))))
		return (NULL);
	elem->s = NULL;
	elem->flag = N_QUOTE;
	elem->next = NULL;
	return (elem);
}

void	push_word(t_word **begin, t_word *new)
{
	t_word	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
}

void		clear_word(t_word *cmd)
{
	if (cmd->s)
		free(cmd->s);
	cmd->s = NULL;
	elem->flag = N_QUOTE;
}

void		destroy_word(t_word **begin)
{
	t_word	*tmp;
	t_word	*list;

	list = *begin;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		clear_word(list);
		free(list);
		list = tmp;
	}
	*begin = NULL;
}
