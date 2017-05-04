/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:12:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 16:24:36 by nbelouni         ###   ########.fr       */
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

typedef struct			s_slist
{
	char				*s;
	struct s_slist		*next;
	struct s_slist		*prev;
}						t_slist;

typedef struct			s_completion
{
	t_slist				*command;
	t_slist				*username;
	t_slist				*hostname;
	t_slist				*variable;
}						t_completion;

/*
**	***************************************************************
**
**
**	Fonctions base struct t_slist
**	sort_list.c
**
**
**	Cree maillon sort_list
*/
t_slist					*create_sort_list(char *s);
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
void					rm_sort_list(t_slist **cmd);
/*
**	supprime toute la liste
*/
void					destroy_sort_list();

int						find_word_begin(char *s, int pos);
int						find_word_end(char *s);
int						find_cplt(char *s, t_slist *r, t_slist **lst, int len);
int						count_sort_lst(t_slist *lst);
int						max_len_sort_lst(t_slist *lst, int n);
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
int						insert_in_list(t_slist **list, char *line);

/*
**	lit PATH, ouvre tous les dossiers, trie leur contenu
**	et met dans t_slist , dans completion.command
*/
int						fill_command(t_slist **list, char *path);
/*
**	lit etc/passwd, parse le contenu et met dans t_slist
**	dans completion.username
*/
int						fill_username(t_slist **list, char *path);
/*
**	lit struct t_env, recupere env.name et met dans t_slist
**	dans completion.variable
*/
int						fill_variable(t_slist **list, t_core *core);
/*
**	lit etc/hosts, parse le contenu et met dans t_slist
**	dans completion.username
*/
int						fill_hostname(t_slist **list, char *path);

int						open_abs_path(char *s, DIR **dirp, int *bg);
int						open_rel_path(char *s, DIR **dirp, int *bg);
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
void					home_tild(t_buf *buf, int *begin);

#endif
