/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:41:10 by dogokar           #+#    #+#             */
/*   Updated: 2017/02/17 14:42:01 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

# define LENLIB  13

t_tree *init_node(void)
{
  t_tree *node;

  if (!(node = ft_memalloc((sizeof(t_tree))))
    return(NULL);
    ft_memset(node, 0, sizeof(node));
    return (node);
}

static  t_lib lib_op[LENLIB]=
{
  {.token = DOT, .priority = 10};
  {.token = OR, .priority = 9};
  {.token = AND, .priority = 9};
  {.token = PIPE, .priority = 8};
  {.token = SL_DIR, .priority = 7};
  {.token = SR_DIR, .priority = 7};
  {.token = AMP, .priority = 7};
  {.token = DL_DIR, .priority = 7};
  {.token = DR_DIR, .priority = 7};
  {.token = DIR_AMP, .priority = 7};
}

t_tree  *add_tree(t_token *lst)
{
  t_tree *node;

  node = ft_memalloc(sizeof(t_token));

  node->token = &lst;
  node->father = NULL;
  node->left = NULL;
  node->right = NULL;
  return (node);
}

t_lib  cheak_lib(t_token *node)
{
    int i;

    i = 0;
    while (i <= LENLIB)
    {
      if (node->token == lib_op[i].token)
        return (lib_op[i]);
        ++i;
    }
    return (NULL);
}

int  compare_token(t_token *node_lst, t_token *tmp, int lvl)
{
  t_lib  lib_lst;
  t_lib  lib_tmp;

  lib_lst = NULL;
  lib_lst = cheak_lib(node_lst);
  lib_tmp = NULL;
  lib_tmp = cheak_lib(node_tmp);
  if (!lib_lst && lib_tmp)
    return(1)
  else if (lib_lst && lib_tmp)
  {
    if (lib_lst.priority < lib_tmp.priority)
      return(1);
    else
      return (0);
  }
  else
    return (0);
}


int  priority(t_token *node_lst, t_token *tmp, int lvl)
{
  if (node_lst == NULL && node_lst->select == 0 && node->bc_level == lvl)
    return (1);
  else if (tmp->bc_level != lvl)
    return (0);
  else if (compare_token(node_lst, tmp))
    return (1);
  else if ()
  return (0);
}

t_token *search_toke(t_token *lst, int bc_lvl)
{
  t_token   *tmp;
  t_token   *node_lst;
  int       max_lvl;

  tmp = lst;
  max_lvl = 0;
  node_lst = NULL;
  while (tmp && tmp->select == 0)
  {
    if (tmp->bt_lvl > max_lvl)
      max_lvl = tmp->bt_lvl;
    if (priority(node_lst, tmp, bt_lvl))
      node_lst = tmp;
    tmp = tmp->next;
  }
  if (node_lst == NULL && max_lvl > 0)
  {
    bc_lvl++;
    return (search_toke(lst, bt_lvl));
  }
  return (node_lst);
}

t_tree  *new_tree(t_token *lst)
{
  t_tree  *node;
  t_tree  *tmp;

  node = NULL;
  tmp = NULL;

  if (lst)
  {
    node = search_toke(lst);
  }
}

void ft_push_ast(t_token *list, t_tree **ast)
{
  t_tree  *head_node;

  head_node = new_tree(list);

}
