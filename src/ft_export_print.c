/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 18:22:46 by dogokar           #+#    #+#             */
/*   Updated: 2017/03/15 18:23:30 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		concatlst(t_lst *head, t_lst *tail)
{
	head->tail->next = tail->head;
	tail->head->prev = head->tail;
	head->size += tail->size;
}

t_elem		*sort_node(t_lst *node)
{
	t_elem	*tmp;
	t_elem	*elem;

	tmp = node->head;
	elem = node->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, elem->name) < 0)
			elem = tmp;
		tmp = tmp->next;
	}
	if (elem)
		ft_extract_elem(&elem, node);
	return (elem);
}

t_lst		*lst_sort_ascii(t_lst *lsthead)
{
	t_elem	*node;
	t_elem	*tmp;
	int		i;
	int		y;

	y = 0;
	node = NULL;
	i = lsthead->size - 1;
	node = sort_node(lsthead);
	tmp = node;
	node->prev = NULL;
	while (y < i)
	{
		node->next = sort_node(lsthead);
		node->next->prev = node;
		node = node->next;
		y++;
	}
	lsthead->head = tmp;
	node->next = NULL;
	lsthead->tail = node;
	return (lsthead);
}

void		ft_print_lst_ex(t_lst *lst, int t)
{
	t_elem	*elem;

	if (lst != NULL)
	{
		elem = lst->head;
		while (elem != NULL)
		{
			if (t >= 1)
				ft_putstr("declare -x ");
			write(1, elem->name, ft_strlen(elem->name));
			write(1, "=", 1);
			if (elem->value != NULL)
			{
				ft_putchar('"');
				write(1, elem->value, ft_strlen(elem->value));
				ft_putchar('"');
			}
			write(1, "\n", 1);
			elem = elem->next;
		}
	}
}

void		ft_print_export(t_set *m_env)
{
	t_lst	*env;
	t_lst	*export;

	env = ft_lstdup(m_env->env);
	if (m_env->exp && m_env->exp->head)
	{
		export = ft_lstdup(m_env->exp);
		concatlst(env, export);
	}
	ft_print_lst_ex(lst_sort_ascii(env), 1);
	if (env)
		ft_del_list(env);
}
