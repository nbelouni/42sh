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

int     test_lvl(int bt_lvl, int bc_lvl, t_lvl *lvl)
{
  if (bt_lvl == lvl->bt_lvl && bc_lvl == lvl->bc_lvl)
  return (0);
  else
  return (1);
}

int  priority(t_token *node_lst, t_token *tmp, t_lvl *lvl)
{
  int tmp_bt;
  int tmp_bc;

  tmp_bt = tmp->bt_level;
  tmp_bc = tmp->bc_level;
  if (!node_lst && tmp->select == 0 && (test_lvl(tmp_bt, tmp_bc, lvl) == 0))
    return (1);
  else if (test_lvl(tmp_bt, tmp_bc, lvl) == 1)
    return (0);
  else if (compare_token_op(node_lst, tmp))
    return (1);
  else if (compare_token_com(node_lst, tmp))
    return (1);
  return (0);
}

t_lvl   *initlvl(int bt_lvl, int bc_lvl)
{
  t_lvl *lvl;

  if (!(lvl = (t_lvl*)malloc(sizeof(t_lvl))))
    return (NULL);
  lvl->bt_lvl = bt_lvl;
  lvl->bc_lvl = bc_lvl;
  return (lvl);
}


t_token *search_toke(t_token *lst, t_lvl *lvl)
{
  t_token   *tmp;
  t_token   *node_lst;
  t_lvl     *lvl_up;
  int       first_time;

  tmp = lst;
  first_time = 0;
  node_lst = NULL;
  lvl_up = NULL;
  if (lvl == NULL)
    lvl = initlvl(0,0);
  if (lst == NULL)
    return (NULL);
  if (tmp->select == 1)
    tmp = tmp->next;
  while (tmp && tmp->select == 0)
  {
    if (first_time == 0 && test_lvl(tmp->bt_level, tmp->bc_level, lvl))
      {
        first_time = 1;
        lvl_up = initlvl(tmp->bt_level, tmp->bc_level);
      }
    if (priority(node_lst, tmp, lvl))
      node_lst = tmp;
    tmp = tmp->next;
  }
  if (lvl)
  ft_memdel((void*)&lvl);
  if (lvl_up && node_lst == NULL)
    node_lst = search_toke(lst, lvl_up);
  return (node_lst);
}

t_token *search_toke_prev(t_token *lst, t_lvl *lvl)
{
  t_token   *tmp;

  tmp = lst;
  if (lst == NULL)
  return (NULL);
  if (tmp->select == 1)
    tmp = tmp->prev;
  while (tmp && tmp->prev && tmp->select == 0)
     tmp  = tmp->prev;
  return (search_toke(tmp, lvl));
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
   if (!(argv = (char **)malloc(sizeof(char*) * i + 1)))
      return (NULL);
   while (tmp && (count <= i -1))
   {
     argv[count] = ft_strdup(tmp->word);
     ++count;
     tmp->select = 1;
     tmp = tmp->next;
   }
   argv[count] = NULL;
   return (argv);
}

void print_tab(char **tabol)
{
  int i;

  i = 0;
  while (tabol[i] != NULL)
  {
    PUT2(tabol[i]);
    PUT2("   ");
    ++i;
  }
}

t_tree *recurs_creat_tree(t_token *lst)
{
  t_token *tmp;
  t_tree  *node;

  tmp = lst;
  node = NULL;
  node = add_tree(tmp);
  node->token = tmp->type;
  if (tmp->type == CMD)
    node->cmd = concate_cmd(tmp);
  else
    node->cmd = NULL;
  node->left = creat_left(tmp);
  node->right= creat_right(tmp);
  return (node);
}

t_tree *creat_left(t_token *lst)
{
  t_token  *tmp;

  tmp = NULL;
  if (!(tmp = search_toke_prev(lst, NULL)))
    return (NULL);
  tmp->select = 1;
  return (recurs_creat_tree(tmp));
}

t_tree   *creat_right(t_token *lst)
{
  t_token  *tmp;

  tmp = NULL;
  if (!(tmp = search_toke(lst, NULL)))
    return(NULL);
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
    tmp = search_toke(lst, NULL);
    tmp->select = 1;
    node = add_tree(tmp);
    node->right = creat_right(tmp);
    node->left = creat_left(tmp);
  }
  return (node);
}



void print_debug_ast(t_tree *node)
{
  if(!node)
  {
    PUT2("\n node = NULL");
    return ;
}
  else
  {
    PUT2("\n node ======>>>>>> ");
    if (node->token == CMD)
        print_tab(node->cmd);
    else
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
      print_debug_ast(node->right);
      print_debug_ast(node->left);
  }
}

void ft_push_ast(t_token *list, t_tree **ast)
{
  t_tree  *head_node;

  (void)ast;

  if (list)
  {
    head_node = new_tree(list);
    print_debug_ast(head_node);
  }
}
