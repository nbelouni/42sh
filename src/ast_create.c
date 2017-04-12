/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:41:10 by dogokar           #+#    #+#             */
/*   Updated: 2017/04/08 19:50:50 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

#define LENLIB  12

t_tree			*init_node(void)
{
	t_tree	*node;

	if (!(node = ft_memalloc(sizeof(t_tree))))
		return (NULL);
	ft_memset(node, 0, sizeof(node));
	return (node);
}

t_lvl			*initlvl(int bt_lvl, int bc_lvl)
{
	t_lvl *lvl;

	if (!(lvl = (t_lvl*)malloc(sizeof(t_lvl))))
		return (NULL);
	lvl->bt_lvl = bt_lvl;
	lvl->bc_lvl = bc_lvl;
	return (lvl);
}

static t_lib	g_lib_op[LENLIB] =
{
	{.toke = DOT, .priority = 11},
	{.toke = OR, .priority = 9},
	{.toke = AND, .priority = 10},
	{.toke = PIPE, .priority = 8},
	{.toke = SL_DIR, .priority = 7},
	{.toke = SR_DIR, .priority = 7},
	{.toke = AMP, .priority = 11},
	{.toke = DL_DIR, .priority = 7},
	{.toke = DR_DIR, .priority = 7},
	{.toke = LR_DIR, .priority = 7},
	{.toke = DIR_L_AMP, .priority = 7},
	{.toke = DIR_R_AMP, .priority = 7},
};

t_tree			*add_tree(t_token *lst)
{
	t_tree *node;

	node = ft_memalloc(sizeof(t_tree));
	node->token_or = lst;
	node->cmd = NULL;
	node->father = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_lib			*cheak_lib(t_token *node)
{
	int i;

	i = 0;
	while (i < LENLIB)
	{
		if (node->type == g_lib_op[i].toke)
			return (&g_lib_op[i]);
		++i;
	}
	return (NULL);
}

/*
** compare les operateur par rappot à la g_lib_op
*/

int				compare_token_op(t_token *node_lst, t_token *tmp)
{
	t_lib	*lib_lst;
	t_lib	*lib_tmp;

	lib_lst = NULL;
	lib_lst = cheak_lib(node_lst);
	lib_tmp = NULL;
	lib_tmp = cheak_lib(tmp);
	if (!lib_lst && lib_tmp)
		return (1);
	else if (lib_lst && lib_tmp)
	{
		if (lib_lst->priority == lib_tmp->priority && lib_lst->priority > 10)
			return (0);
		if (lib_lst->priority <= lib_tmp->priority)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int				compare_token_com(t_token *node_lst, t_token *tmp)
{
	if (!node_lst && tmp->type == CMD)
		return (1);
	return (0);
}

int				test_lvl(int bt_lvl, int bc_lvl, t_lvl *lvl)
{
	if (bt_lvl == lvl->bt_lvl && bc_lvl == lvl->bc_lvl)
		return (0);
	else
		return (1);
}

/*
**    regle pour parser la liste et inserer les token au bon endroit
*/

int				priority(t_token *node_lst, t_token *tmp, t_lvl *lvl)
{
	int		tmp_bt;
	int		tmp_bc;

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

/*
** fonction qui va chercher le bon element dans la list
** recursive lorsqu'il trouve plus d'element et que le bt
** ou bc lvl est incrementer
*/

t_token			*search_toke(t_token *lst, t_lvl *lvl)
{
	t_token	*tmp;
	t_token	*node_lst;
	t_lvl	*lvl_up;
	int		first_time;

	tmp = lst;
	first_time = 0;
	node_lst = NULL;
	lvl_up = NULL;
	if (lst == NULL)
		return (NULL);
	if (lvl == NULL)
		lvl = initlvl(0, 0);
	if (tmp->select == 1)
		tmp = tmp->next;
	while (tmp && tmp->select == 0)
	{
		if (first_time == 0 && test_lvl(tmp->bt_level, tmp->bc_level, lvl))
		{
			first_time = 1;
			if (lvl_up)
				free(lvl_up);
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

/*
** remonte la liste
*/

t_token			*search_toke_prev(t_token *lst, t_lvl *lvl)
{
	t_token	*tmp;

	tmp = lst;
	if (lst == NULL)
		return (NULL);
	if (tmp->select == 1)
		tmp = tmp->prev;
	while (tmp && tmp->prev && tmp->select == 0)
		tmp = tmp->prev;
	return (search_toke(tmp, lvl));
}

/*
** cree le char **  ex: ls -la tmp
*/

void			cmd_len(t_token *lst, int *i, int *j)
{
	t_token	*tmp;
	int		tmpi;

	tmp = lst;
	tmpi = 0;
	while (tmp && (tmp->type == CMD || tmp->type == ARG))
	{
		if ((tmpi = ft_strlen(tmp->word)) >= *j)
			*j = tmpi;
		*i = *i + 1;
		tmp = tmp->next;
	}
}

char			**concate_cmd(t_token *lst)
{
	t_token	*tmp;
	int		i;
	int		j;
	int		count;
	char	**argv;

	tmp = lst;
	count = 0;
	i = 0;
	j = 0;
	cmd_len(tmp, &i, &j);
	argv = NULL;
	if (!(argv = (char **)malloc(sizeof(char*) * (i * j + 1))))
		return (NULL);
	argv[i * j] = NULL;
	while (tmp && (count <= i - 1))
	{
		argv[count] = ft_strdup(tmp->word);
		++count;
		tmp->select = 1;
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}

/*
** print le char ** pour le debug
*/

void			print_tab(char **tabol)
{
	int		i;

	i = 0;
	while (tabol[i] != NULL)
	{
		PUT2(tabol[i]);
		PUT2("   ");
		++i;
	}
}

/*
** recursive de creation de ast
*/

char			**copy_fd(t_token *tmp)
{
	char	**cmd;

	if (!(cmd = ft_memalloc(sizeof(char *) * 2)))
		return (NULL);
	if (tmp && tmp->word)
	{
		cmd[0] = ft_strdup(tmp->word);
		cmd[1] = NULL;
		return (cmd);
	}
	else
		return (NULL);
}

t_tree			*recurs_creat_tree(t_token *lst)
{
	t_token	*tmp;
	t_tree	*node;

	tmp = lst;
	node = NULL;
	node = add_tree(tmp);
	node->token = tmp->type;
	if (tmp->type == CMD)
		node->cmd = concate_cmd(tmp);
	if (is_dir_type(tmp->type))
		node->cmd = copy_fd(tmp);
	if (tmp->type == TARGET)
		node->cmd = copy_fd(tmp);
	node->right = creat_right(tmp, NULL);
	if (node->right)
		node->right->father = node;
	node->left = creat_left(tmp, NULL);
	if (node->left)
		node->left->father = node;
	return (node);
}

/*
** branche de gauche
*/

t_tree			*creat_left(t_token *lst, t_lvl *lvl)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(tmp = search_toke_prev(lst, lvl)))
		return (NULL);
	tmp->select = 1;
	return (recurs_creat_tree(tmp));
}

/*
** branche de droite
*/

t_tree			*creat_right(t_token *lst, t_lvl *lvl)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(tmp = search_toke(lst, lvl)))
		return (NULL);
	tmp->select = 1;
	return (recurs_creat_tree(tmp));
}

/*
** cree la tete de ast
*/

t_tree			*new_tree(t_token *lst)
{
	t_tree	*node;
	t_token	*tmp;

	node = NULL;
	tmp = NULL;
	if (lst)
	{
		tmp = search_toke(lst, NULL);
		tmp->select = 1;
		node = add_tree(tmp);
		node->token = tmp->type;
		if (tmp->type == CMD)
			node->cmd = concate_cmd(tmp);
		if (is_dir_type(tmp->type))
			node->cmd = copy_fd(tmp);
		if (tmp->type == TARGET)
			node->cmd = copy_fd(tmp);
		node->right = creat_right(tmp, NULL);
		if (node->right)
			node->right->father = node;
		node->left = creat_left(tmp, NULL);
		if (node->left)
			node->left->father = node;
	}
	return (node);
}

/*
**  print ast pour le debug
*/

void			print_debug_ast(t_tree *node)
{
	if (!node)
	{
		PUT2("\n node = NULL");
		return ;
	}
	if (node->left)
	{
		PUT2(" \n node->left");
		print_debug_ast(node->left);
	}
	PUT2("\n node ======>>>>>> ");
	if (node->right)
	{
		PUT2(" \n node->right");
		print_debug_ast(node->right);
	}
	PUT2(" \n up");
}

void			free_content_ast(t_tree *node)
{
	if (node->cmd != NULL)
		ft_tabdel(node->cmd);
	node->cmd = NULL;
}

void			free_ast(t_tree *ast)
{
	if (!ast)
	{
		return ;
	}
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	free_content_ast(ast);
	free(ast);
}

void			ft_push_ast(t_token *list, t_tree **ast)
{
	t_tree	*head_node;

	if (list)
	{
		head_node = new_tree(list);
		*ast = head_node;
	}
}
