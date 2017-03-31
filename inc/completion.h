/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:49:27 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/30 19:29:10 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

#include <42sh.h>

# define COMPLETE_LINE	134

typedef struct s_elem	t_elem;
typedef struct s_lst	t_lst;
typedef struct s_buf	t_buf;

typedef struct			s_completion
{
	t_list				*command;
	t_list				*username;
	t_list				*hostname;
	t_list				*variable;
}						t_completion;

#define LIST_S(list)	((char *)(list->content))

void					s_del(void *data, size_t len);

/*
**	***************************************************************
*/
/*
**	Fonctions base struct t_completion
**	edit_completion.c
*/
/*
**	trie par ordre ascii, n'ajoute pas de maillon si string deja existante
*/
int						insert_in_list(t_list **list, char *line);

/*
**	lit PATH, ouvre tous les dossiers, trie leur contenu
**	et met dans t_list , dans completion.command
*/
int						fill_command(t_list **list, char *path);
/*
**	lit etc/passwd, parse le contenu et met dans t_list
**	dans completion.username
*/
int						fill_username(t_list **list, char *path);
/*
**	lit struct t_env, recupere env.name et met dans t_list
**	dans completion.variable
*/
int						fill_variable(t_list **list, t_elem *env);
/*
**	lit etc/hosts, parse le contenu et met dans t_list
**	dans completion.username
*/
int						fill_hostname(t_list **list, char *path);

/*
**	appelle fill_*()
**	initialise t_completion
*/
int						init_completion(t_completion *cplt, t_lst *env);

/*
**	complete buf.line selon matches entre input et t_completion
**	completion.c
*/
int						complete_line(t_buf *buf, t_completion *completion, char x);

#endif
