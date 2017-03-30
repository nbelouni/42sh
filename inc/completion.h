/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:49:27 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 17:11:42 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

# include <42sh.h>

# define COMPLETE_LINE	134

typedef struct s_core	t_core;
typedef struct s_elem	t_elem;
typedef struct s_lst	t_lst;
typedef struct s_buf	t_buf;

typedef struct			s_sort_list
{
	char				*s;
	struct s_sort_list	*next;
	struct s_sort_list	*prev;
}						t_sort_list;

typedef struct			s_completion
{
	t_sort_list			*command;
	t_sort_list			*username;
	t_sort_list			*hostname;
	t_sort_list			*variable;
}						t_completion;

/*
**	***************************************************************
**
**
**	Fonctions base struct t_sort_list
**	sort_list.c
**
**
**	Cree maillon sort_list
*/
t_sort_list				*create_sort_list(char *s);
/*
**	ajoute a la fin un maillon sort_list
*/
void					push_sort_list();
/*
**	clear maillon
*/
void					clear_sort_list();
/*
**	supprime maillon
*/
void					rm_sort_list(t_sort_list **cmd);
/*
**	supprime toute la liste
*/
void					destroy_sort_list();

/*
**	***************************************************************
**
**
**	Fonctions base struct t_completion
**	edit_completion.c
**
**
**	trie par ordre ascii, n'ajoute pas de maillon si string deja existante
*/
int						insert_in_list(t_sort_list **list, char *line);

/*
**	lit PATH, ouvre tous les dossiers, trie leur contenu
**	et met dans t_sort_list , dans completion.command
*/
int						fill_command(t_sort_list **list, char *path);
/*
**	lit etc/passwd, parse le contenu et met dans t_sort_list
**	dans completion.username
*/
int						fill_username(t_sort_list **list, char *path);
/*
**	lit struct t_env, recupere env.name et met dans t_sort_list
**	dans completion.variable
*/
int						fill_variable(t_sort_list **list, t_core *core);
/*
**	lit etc/hosts, parse le contenu et met dans t_sort_list
**	dans completion.username
*/
int						fill_hostname(t_sort_list **list, char *path);

/*
**	appelle fill_*()
**	initialise t_completion
*/
int						init_completion(t_completion *cplt, t_core *core);

/*
**	complete buf.line selon matches entre input et t_completion
**	completion.c
*/
int						complete_line(t_buf *buf, t_completion *cplt, char x);

#endif
