/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:41:10 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 18:18:49 by nbelouni         ###   ########.fr       */
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

static t_lib	g_lib_op[LENLIB] =
{
	{.toke = DOT, .priority = 11},
	{.toke = OR, .priority = 10},
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

static t_lib	*check_lib(t_token *node)
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
	lib_lst = check_lib(node_lst);
	lib_tmp = NULL;
	lib_tmp = check_lib(tmp);
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

/*
**    regle pour parser la liste et inserer les token au bon endroit
*/

int				priority(t_token *node_lst, t_token *tmp)
{
	if (!node_lst && tmp->select == 0)
		return (1);
	else if (compare_token_op(node_lst, tmp))
		return (1);
	else if (!node_lst && tmp->type == CMD)
		return (1);
	return (0);
}

/*
** fonction qui va chercher le bon element dans la list
** recursive lorsqu'il trouve plus d'element et que le bt
** ou bc lvl est incrementer
*/

t_token			*search_toke(t_token *lst)
{
	t_token	*tmp;
	t_token	*node_lst;

	tmp = lst;
	node_lst = NULL;
	if (lst == NULL)
		return (NULL);
	if (tmp->select == 1)
		tmp = tmp->next;
	while (tmp && tmp->select == 0)
	{
		if (priority(node_lst, tmp))
			node_lst = tmp;
		tmp = tmp->next;
	}
	return (node_lst);
}

/*
** remonte la liste
*/

t_token			*search_toke_prev(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	if (lst == NULL)
		return (NULL);
	if (tmp->select == 1)
		tmp = tmp->prev;
	while (tmp && tmp->prev && tmp->select == 0)
		tmp = tmp->prev;
	return (search_toke(tmp));
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
	while (tmp && tmp->word && (count <= i - 1))
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
	{
		free(cmd);
		return (NULL);
	}
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
	node->right = creat_right(tmp);
	if (node->right)
		node->right->father = node;
	node->left = creat_left(tmp);
	if (node->left)
		node->left->father = node;
	return (node);
}

/*
** branche de gauche
*/

t_tree			*creat_left(t_token *lst)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(tmp = search_toke_prev(lst)))
		return (NULL);
	tmp->select = 1;
	return (recurs_creat_tree(tmp));
}

/*
** branche de droite
*/

t_tree			*creat_right(t_token *lst)
{
	t_token	*tmp;

	tmp = NULL;
	if (!(tmp = search_toke(lst)))
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
		tmp = search_toke(lst);
		tmp->select = 1;
		node = add_tree(tmp);
		node->token = tmp->type;
		if (tmp->type == CMD)
			node->cmd = concate_cmd(tmp);
		if (is_dir_type(tmp->type))
			node->cmd = copy_fd(tmp);
		if (tmp->type == TARGET)
			node->cmd = copy_fd(tmp);
		node->right = creat_right(tmp);
		if (node->right)
			node->right->father = node;
		node->left = creat_left(tmp);
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
