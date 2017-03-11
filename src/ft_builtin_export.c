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

void print_lst(t_set *node, int mode)
{
  t_elem *head;
  if (mode == 1)
    head = node->set->head;
  else if (mode == 2)
    head = node->env->head;
  else
    head = node->exp->head;
  while (head)
  {
    PUT2(head->name);
    PUT2("\n");
    head = head->next;
  }
}

/*
**          va trier les differents list a la vole (pas le choix trop prise de tete)
*/
// t_lst       *lst_sort_ascii(t_lst *node)
// {
//   t_sort_lst *head;
//   t_lst       *tmp;
//
//   head = NULL;
//   tmp = node;
//
// }

// int			ft_export(t_lst *lst, char *arg)
// {
// 	char	*name;
// 	char	*val;
// 	int		ret;
//
// 	if ((name = ft_strsub(arg, 0, ft_get_index_of(arg, '='))) == NULL)
// 		return (ERR_EXIT);
// 	ret = 0;
// 	if (name == NULL || name[0] == '\0' || name[0] == '=')
// 		return (ft_print_error("42sh", ERR_ARG_INVALID, ERR_NEW_CMD));
// 	val = NULL;
// 	if ((ft_strlen(name) + 1) < ft_strlen(arg))
// 	{
// 		if ((val = ft_strsub(arg, ft_strlen(name) + 1, \
// 				(ft_strlen(arg) - ft_strlen(name) + 1))) == NULL)
// 			return (ft_free_and_return(ERR_EXIT, name, NULL));
// 	}
// 	ret = ft_setenv(lst, name, val);
// 	(val != NULL) ? ft_multi_free(val, name, NULL, NULL) : ft_strdel(&name);
// 	return (ret);
// }

// int  is_word(char *argv, t_set *m_env)
// {
//   int    i;
//   char  name;
//
//   i = ft_get_index_of(argv, '=');
//   if (argv[0] == '=')
//   {
//     ft_putendl("string not format");
//     return (FALSE);
//   }
//   if (i > 0)
//     return (0);
//
// }

t_elem *cut_lst(t_elem *lst)
{
  t_elem *tmp;

  tmp = lst;
  if (tmp->next)
    tmp->next->prev = tmp->prev;
  if (tmp->prev)
    tmp->prev->next = tmp->next;
  tmp->next = NULL;
  tmp->prev = NULL;
  return (tmp);
}

void move_to_env(t_elem *lst, t_lst *env)
{
  t_elem *node;
  t_elem *tmp;

  tmp = env->head;
  node = cut_lst(lst);
  while(tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = node;
  node->prev = tmp;
}

int insert_to_env(t_elem *node, char *arg, t_lst *env)
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
    }
    move_to_env(node, env);
  //ret = ft_setenv(env)
    return (0);
}

t_elem  *search_var(char *arg, t_lst *type_env)
{
  t_elem *node;
  t_elem *tmp;
  char  *name;

  tmp = NULL;
  node = type_env->head;
	name = ft_strsub(arg, 0, ft_get_index_of(arg, '='));
  if (name == NULL || name[0] == '\0' || name[0] == '=')
    return (NULL);
  while (node)
  {
    if (ft_strcmp(node->name, name) == 0)
    {
      tmp = node;
      break;
    }
      node = node->next;
  }
  ft_strdel(&name);
  if (!tmp)
      return (NULL);
  return (tmp);
}

int multi_var_cheak(char *argv, t_set *m_env)
{
  t_elem *tmp;

  tmp = NULL;
  if ((tmp = search_var(argv, m_env->exp)))
    return (insert_to_env(tmp, argv, m_env->env));
  else if ((tmp = search_var(argv, m_env->set)))
    return (insert_to_env(tmp, argv, m_env->env));
  else if ((tmp = search_var(argv, m_env->env)))
    return (insert_to_env(tmp, argv, m_env->env));
  return (-1);
}

int ft_builtin_export(char **argv, t_set *m_env)
{
  int *opt;
  int i;
  int result;

  opt = ft_opt_parse(EXPORT_OPT, argv, 0);
  i = 0;
  i = opt[1];
  result = 0;
  while (argv[i] != NULL)
  {
    // if (is_word(arv, m_env))
    //   return (TRUE);
    result = multi_var_cheak(argv[i], m_env);
    ++i;
  }
  return (result);
}
