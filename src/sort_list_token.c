/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:51:24 by alallema          #+#    #+#             */
/*   Updated: 2017/03/24 17:05:37 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
**	A check si pas de cmd avant token redir
*/

t_token	*move_for_token(t_token *elem)
{
	t_token	*tmp;
	t_token	*ret;

	tmp = elem->prev;
	while (tmp->prev && (tmp->type == TARGET || is_dir_type(tmp->type)))
		tmp = tmp->prev;
	if (!is_dir_type(tmp->type))
		tmp = tmp->next;
	ret = elem->next;
	if (tmp && tmp->prev)
	{
		tmp = tmp->prev;
		elem->prev->next = elem->next;
		if (elem->next)
			elem->next->prev = elem->prev;
		elem->next = tmp->next;
		tmp->next = elem;
		elem->prev = tmp;
		if (elem->next)
			elem->next->prev = elem;
		elem->type = ARG;
	}
	else if (tmp && !tmp->prev)
	{
		if (ret)
			ret->prev = elem->prev;
		elem->prev->next = elem->next;
		elem->next = tmp;
		tmp->prev = elem;
		elem->prev = NULL;
		elem->type = CMD;
		ft_print_token_list(&elem);
	}
	return (ret);
}

void	check_target_place(t_token **list)
{
	t_token	*elem;

	elem = *list;
	elem = elem->next;
	while (elem && elem->prev && elem->type == CMD)
		elem = move_for_token(elem);
	if (elem && !elem->prev)
		*list = elem;
}

int		check_error_out(t_token *elem)
{
	int		i;

	i = 0;
	if (elem && elem->type == TARGET)
	{
		if (elem->word[0] == '-')
			return (0);
		while (elem->word[i])
		{
			if (ft_isdigit(elem->word[i]) == 0)
				return (ERR_FD);
			i++;
		}
	}
	return (0);
}

void	ft_swap_in(t_token **list)
{
	char	*s;
	int		ret;

	ret = 2;
	if ((*list)->next->type == DIR_L_AMP || (*list)->next->type == DIR_R_AMP)
		ret = 3;
	s = (*list)->next->word;
	(*list)->next->word = (*list)->word;
	(*list)->word = s;
//	s = ft_memalloc(ft_strlen((*list)->word) + ret);
//	s = ft_strcpy(s, (*list)->word);
//	ft_memcpy(&s[ft_strlen((*list)->word)], (*list)->next->word,
//	ft_strlen((*list)->next->word));
//	if ((*list)->next && (*list)->next->word) 
//		free((*list)->next->word);
//	(*list)->next->word = s;
	ft_tokenclear(list);
}

void	ft_find_fd(t_token *list)
{
	char	*s;

	s = NULL;
	if (list && list->prev && list->prev->type != FD_IN)
	{
		free(list->word);
		list->word = ft_strdup("1");
	}
}

/*
**	Faut faire des check avant de trier la liste, pour l'instant on garde ca
**	On oublie les commentaires, c'est beaucoup trop chiant
*/

int		sort_list_token(t_token **list, t_completion *completion)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
//		if (isRedir(elem->type))
//			ft_find_fd(elem);
		if (elem->type == FD_IN)
		{
			ft_swap_in(&elem);
			if (!elem->prev)
				*list = elem;
		}
		if ((elem->type == DIR_L_AMP || elem->type == DIR_R_AMP) && elem->next && check_error_out(elem->next))
			return (ft_print_error(elem->word, ERR_FD_AMB, ERR_FD));
		if (((elem->type > START && elem->type < AMP) || (elem->type > AND
			&& elem->type < DIR_L_AMP)) && elem->next && elem->next->type == CMD)
			elem->next->type = TARGET;
		if (elem->type == TARGET && elem->next &&
		(elem->next->type == CMD || elem->next->type == ARG))
		{
			check_target_place(&elem);
			if (elem && !elem->prev)
				*list = elem;
		}
		if (elem->type == CMD && elem->prev && (elem->prev->type == CMD
		|| elem->prev->type == ARG))
			elem->type = ARG;
		if (elem->type == DL_DIR)
			here_doc(elem->next, completion);
		if (elem->type == CMD)
		{
			elem = is_local_var(elem);
		}
		elem = elem->next;
	}
	while ((*list) && (*list)->prev)
		(*list) = (*list)->prev;
	return (0);
}
