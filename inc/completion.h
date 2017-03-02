/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 14:49:27 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/02 19:55:43 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		COMPLETION_H
# define	COMPLETION_H

#include <42sh.h>

# define COMPLETE_LINE	134

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

t_sort_list			*create_sort_list(char *s);
void				push_sort_list();
void				clear_sort_list();
void				rm_sort_list(t_sort_list **cmd);
void				destroy_sort_list();

int					insert_in_list(t_sort_list **list, char *line);

int					fill_command(t_sort_list **list, char *path);
int					fill_username(t_sort_list **list, char *path);
int					fill_variable(t_sort_list **list, t_elem *env);
int					fill_hostname(t_sort_list **list, char *path);

int					init_completion(t_completion *cplt, t_lst *env);
int					complete_line(t_buf *buf, t_completion *completion, char x);

#endif
