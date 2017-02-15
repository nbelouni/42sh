/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 20:26:22 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/15 20:40:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token	*create_token(void)
{
	t_token	*elem;

	if (!(elem = ft_memalloc(sizeof(t_token))))
		return (NULL);
	type = NO_TOKEN;
	n_word = 0;
	word = NULL;
	bt_level = 0;
	bc_level = 0;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	push_token(t_token **begin, t_token *new)
{
	t_token	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->prev = elem;
}

void		clear_token(t_token *cmd)
{
	type = NO_TOKEN;
	n_word = 0;
	if (cmd->word)
		destroy(cmd->word);
	cmd->word = NULL;
	bt_level = 0;
	bc_level = 0;
}

void		destroy_token(t_token **begin)
{
	t_token	*tmp;
	t_token	*list;

	list = *begin;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		clear_token(list);
		free(list);
		list = tmp;
	}
	*begin = NULL;
}
