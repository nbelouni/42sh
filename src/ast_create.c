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

# define LENLIB  10

t_tree *init_node(void)
{
  t_tree *node;

  if (!(node = ft_memalloc(sizeof(t_tree))))
    return(NULL);
    ft_memset(node, 0, sizeof(node));
  return (node);
}

static  t_lib lib_op[LENLIB] =
{
  {.toke = DOT, .priority = 10},
  {.toke = OR, .priority = 9},
  {.toke = AND, .priority = 9},
  {.toke = PIPE, .priority = 8},
  {.toke = SL_DIR, .priority = 7},
  {.toke = SR_DIR, .priority = 7},
  {.toke = AMP, .priority = 7},
  {.toke = DL_DIR, .priority = 7},
  {.toke = DR_DIR, .priority = 7},
  {.toke = DIR_AMP, .priority = 7},
};

t_tree  *add_tree(t_token *lst)
{
  t_tree *node;

  node = ft_memalloc(sizeof(t_tree));
  node->token_or = lst;
  node->father = NULL;
  node->left = NULL;
  node->right = NULL;
  return (node);
}

t_lib  *cheak_lib(t_token *node)
{
    int i;

    i = 0;
    while (i <= LENLIB)
    {
      if (node->type == lib_op[i].toke)
        return (&lib_op[i]);
        ++i;
    }
    return (NULL);
}

int  compare_token_op(t_token *node_lst, t_token *tmp)
{
  t_lib  *lib_lst;
  t_lib  *lib_tmp;


  lib_lst = NULL;
  lib_lst = cheak_lib(node_lst);
  lib_tmp = NULL;
  lib_tmp = cheak_lib(tmp);
  if (!lib_lst && lib_tmp)
    return(1);
  else if (lib_lst && lib_tmp)
  {
    if (lib_lst->priority < lib_tmp->priority)
      return(1);
    else
      return (0);
  }
  else
    return (0);
}

int  compare_token_com(t_token *node_lst, t_token *tmp)
{
  if(!node_lst && tmp->type == CMD)
      return (1);
  return (0);
}

int  priority(t_token *node_lst, t_token *tmp, int lvl)
{
  if (!node_lst && tmp->select == 0 && tmp->bt_level == lvl)
    return (1);
  else if (tmp->bt_level != lvl)
    return (0);
  else if (compare_token_op(node_lst, tmp))
    return (1);
  else if (compare_token_com(node_lst, tmp))
    return (1);
  return (0);
}

t_token *search_toke(t_token *lst, int bt_level)
{
  t_token   *tmp;
  t_token   *node_lst;
  int       max_lvl;

  tmp = lst;
  max_lvl = 0;
  node_lst = NULL;
  if (lst == NULL)
  return (NULL);
  if (tmp->select == 1)
  {
    PUT2("\n test 2");
    PUT2(tmp->word);
    tmp = tmp->next;
  }
  while (tmp && tmp->select == 0)
  {
    if (tmp->bt_level > max_lvl)
      max_lvl = tmp->bt_level;
    if (priority(node_lst, tmp, bt_level))
      node_lst = tmp;
    tmp = tmp->next;
  }
  //if (node_lst == NULL && max_lvl > 0)
    //return (search_toke(lst, bt_level + 1));
  return (node_lst);
}

t_token *search_toke_prev(t_token *lst, int bt_lvl)
{
  t_token   *tmp;

  tmp = lst;
  if (lst == NULL)
  return (NULL);
  if (tmp->select == 1)
    tmp = tmp->prev;
  while (tmp && tmp->prev && tmp->select == 0)
     tmp  = tmp->prev;
  return (search_toke(tmp, bt_lvl));
}

int   cmd_len(t_token *lst)
{
  t_token *tmp;
  int i;

  tmp = lst;
  i = 0;
  while (tmp && (tmp->type == CMD || tmp->type == ARG))
  {
    tmp = tmp->next;
    ++i;
  }
  return (i);
}

char  **concate_cmd(t_token *lst)
 {
   t_token *tmp;
   int      i;
   int       count;
   char     **argv;

   tmp = lst;
   count = 0;
   i = cmd_len(tmp);
   if (!(argv = (char **)malloc(sizeof(char) * i + 1)))
      return (NULL);
   while (tmp && count <= i)
   {
     argv[count] = ft_strdup(tmp->word);
     ++count;
     tmp->select = 1;
     tmp = tmp->next;
   }
   argv[count] = NULL;
   return (argv);
}

t_tree *recurs_creat_tree(t_token *lst)
{
  t_token *tmp;
  t_tree  *node;

  tmp = lst;
  node = NULL;
  node = add_tree(tmp);
  if (tmp->type == CMD)
  node->cmd = concate_cmd(tmp);
  node->left = creat_left(tmp);
  node->right= creat_right(tmp);
  return (node);
}

t_tree *creat_right(t_token *lst)
{
  t_token  *tmp;

  tmp = NULL;
  if (!(tmp = search_toke_prev(lst,0)))
    return (NULL);
  tmp->select = 1;
  return (recurs_creat_tree(tmp));
}

t_tree   *creat_left(t_token *lst)
{
  t_token  *tmp;

  tmp = NULL;
  if (!(tmp = search_toke(lst, 0)))
  {
    PUT2("wtf");
    return(NULL);
  }
  tmp->select = 1;
  return (recurs_creat_tree(tmp));
}

t_tree  *new_tree(t_token *lst)
{
  t_tree  *node;
  t_token  *tmp;

  node = NULL;
  tmp = NULL;
  if (lst)
  {
    tmp = search_toke(lst, 0);
    tmp->select = 1;
    node = add_tree(tmp);
    node->left = creat_left(tmp);
    node->right = creat_right(tmp);
  }
  return (node);
}

void print_debug_ast(t_tree *node)
{
  if(!node)
  {
    PUT2(" node = NULL");
    return ;
}
  else
  {
    PUT2("\n node = ");
    PUT2(node->token_or->word);
    if (node->left)
    {
      PUT2(" \n node->left = ");
      PUT2(node->left->token_or->word);
  }
  else
    PUT2("\n node->left = NULL");
    if (node->right)
    {
      PUT2(" \n node->right = ");
      PUT2(node->right->token_or->word);
    }
    else
    PUT2("\n node->right = NULL");
    print_debug_ast(node->left);
    print_debug_ast(node->right);
  }
}

void ft_push_ast(t_token *list, t_tree **ast)
{
  t_tree  *head_node;

  (void)ast;
  head_node = new_tree(list);

  print_debug_ast(head_node);
}
