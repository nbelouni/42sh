  /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 10:39:48 by dogokar           #+#    #+#             */
/*   Updated: 2017/03/05 10:39:53 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  opt[0] == retour erreur ou position fin option d'args.
**  opt[1] -> si p trouve, 1, sinon 0*
*/

#include "42sh.h"

/*
**          va trier les differents list a la vole (pas le choix trop prise de tete)
**          sois utiliser un struc de tri avec un void content
**          (=) exseption quand c'est une vars export
**          supposition export fais un arbre
*/

void move_to_env(t_elem *lst, t_lst *env, t_lst *type_env)
{
  ft_extract_elem(&lst, type_env);
  ft_insert_elem(lst, env);
}

int insert_to_env(t_elem *node, char *arg, t_lst *env, t_lst *type_env)
{
  char *val;
  int  ret;

  ret = 0;
  val = NULL;
  if ((ft_strlen(node->name) + 1) < ft_strlen(arg))
  {
		if ((val = ft_strsub(arg, ft_strlen(node->name) + 1,
    (ft_strlen(arg) - ft_strlen(node->name) + 1))) == NULL)
  			return (ft_free_and_return(ERR_EXIT, node->name, NULL));
  	}
    if (val)
    {
      ft_strdel(&node->value);
      node->value = ft_strdup(val);
      ft_strdel(&val);
    }
    if (type_env)
    move_to_env(node, env, type_env);
    return (0);
}

t_elem  *search_var(char *arg, t_lst *type_env)
{
  t_elem *tmp;
  char  *name;

  tmp = NULL;
  if (ft_strchr(arg, '='))
  {
    if (!(name = ft_strsub(arg, 0, ft_get_index_of(arg, '='))))
    return (NULL);
  }
  else
  name = ft_strdup(arg);
  if (name == NULL || name[0] == '\0' || name[0] == '=')
    return (NULL);
  if (!(tmp = ft_find_elem(name, type_env)))
  {
    ft_strdel(&name);
    return (NULL);
  }
  ft_strdel(&name);
  return (tmp);
}

int			ft_add_elemo(t_lst *lst, char *s)
{
	t_elem	*elem;

	elem = NULL;
	if (s && s[0])
	{
			if ((elem = ft_init_elem()) == NULL)
        return (ERR_EXIT);
      elem->name = ft_strdup(s);
			ft_insert_elem(elem, lst);
			return (0);
	}
	return (-1);
}

int insert_to_exp(char *argv, t_set *m_env)
{
  char *tmp;
  int   result;

  tmp = NULL;
  result = 0;
  if (!ft_strchr(argv, '='))
  {
    if (!m_env->exp)
      m_env->exp = ft_init_list();
      ft_add_elemo(m_env->exp, argv);
      return (0);
  }
  else
    ft_export(m_env->env, argv);
  return (0);
}

void concatlst(t_lst *head, t_lst *tail)
{
  head->tail->next = tail->head;
  tail->head->prev = head->tail;
  head->size += tail->size;
}

int multi_var_cheak(char *argv, t_set *m_env)
{
  t_elem *tmp;

  tmp = NULL;
  if ((tmp = search_var(argv, m_env->exp)))
    return (insert_to_env(tmp, argv, m_env->env, m_env->exp));
  else if ((tmp = search_var(argv, m_env->set)))
    return (insert_to_env(tmp, argv, m_env->env, m_env->set));
  else if ((tmp = search_var(argv, m_env->env)))
    return (insert_to_env(tmp, argv, m_env->env, NULL));
  else if (!tmp && argv)
    return (insert_to_exp(argv, m_env));
  return (-1);
}

t_elem   *sort_node(t_lst *node)
{
  t_elem *tmp;
  t_elem *elem;

  tmp = node->head;
  elem = node->head;
  while (tmp)
  {
    if (ft_strcmp(tmp->name,elem->name) < 0)
      elem = tmp;
    tmp = tmp->next;
  }
  if (elem)
  ft_extract_elem(&elem, node);
  return (elem);
}

t_elem    *lst_sort_ascii(t_lst *lsthead)
{
  t_elem *node;
  t_elem *tmp;
  int i;
  int y;

  y = 0;
  node = NULL;
  i = lsthead->size;
  node = sort_node(lsthead);
  tmp = node;
  while (y < (i - 1))
  {
    node->next = sort_node(lsthead);
    node->next->prev = node;
    node = node->next;
    y++;
  }
  lsthead->head = tmp;
  return (tmp);
}

void ft_print_lst_ex(t_lst *lst, int t)
{
  t_elem *elem;

  if (lst != NULL)
  {
    elem = lst_sort_ascii(lst);
    while (elem != NULL)
    {
      if (t >= 1)
      ft_putstr("declare -x ");
      write(1, elem->name, ft_strlen(elem->name));
      write(1, "=", 1);
      if (elem->value != NULL)
      {
        write(1, elem->value, ft_strlen(elem->value));
      }
      write(1, "\n", 1);
      elem = elem->next;
    }
  }
}

void ft_print_export(t_set *m_env)
{
  t_lst *env;
  t_lst *export;

  env = ft_lstdup(m_env->env);
  if (m_env->exp && m_env->exp->head)
  {
    export = ft_lstdup(m_env->exp);
    concatlst(env, export);
  }
  ft_print_lst_ex(env, 1);
}

int ft_builtin_export(char **argv, t_set *m_env)
{
  int *opt;
  int i;
  int result;

  opt = ft_opt_parse(EXPORT_OPT, argv, 0);
  i = 0;
  i = opt[1];
  i++;
  result = 0;
  if (argv[1] == NULL)
    ft_print_export(m_env);
  while (argv[i] != NULL)
  {
    result = multi_var_cheak(argv[i], m_env);
    ++i;
  }
  return (result);
}
