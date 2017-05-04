/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:07:13 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

/*
** concate les list exp et env pour les trier
*/

void		concatlst(t_lst *head, t_lst *tail)
{
	head->tail->next = tail->head;
	tail->head->prev = head->tail;
	head->size += tail->size;
	tail->head = NULL;
	tail->tail = NULL;
}

/*
**  va chercher le bon element de la liste a q trier (trie par insertion)
*/

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

/*
**			va trier la liste en ascii
*/

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

/*
**  print la list concatener et trier
*/

void		ft_print_lst_ex(t_lst *lst, int t)
{
	t_elem	*elem;

	elem = NULL;
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

/*
**   va cree une list temporaire qui va etre supprimer apres l'affchage
*/

void		ft_print_export(t_core *m_env)
{
	t_lst	*env;
	t_lst	*export;

	export = NULL;
	env = (m_env->env && m_env->env->head) ? ft_lstdup(m_env->env) : NULL;
	export = (m_env->exp && m_env->exp->head) ? ft_lstdup(m_env->exp) : NULL;
	if (env && export)
		concatlst(env, export);
	if (env)
		ft_print_lst_ex(lst_sort_ascii(env), 1);
	else if (!env && export)
		ft_print_lst_ex(lst_sort_ascii(export), 1);
	(env) ? ft_del_list(env) : 0;
	(export) ? ft_del_list(export) : 0;
}
