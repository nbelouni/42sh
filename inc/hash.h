/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 20:03:51 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/20 21:08:11 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/queue.h>
# include <strings.h>
# include <stdint.h>
# include "42sh.h"
# include "list.h"

# define CAST(t, v)		((t)(v))
# define HASH(t)		(t->vec)
# define KEY(n)			(n->key)
# define CDATA(n)		(n->data)
# define LEN(t)			(t->len)
# define GETPOS(k, t)	(KEY(k) % LEN(t))

typedef struct	s_entry
{
	uint32_t	key;
	void		*data;
}				t_entry;

typedef struct	s_table
{
	List_p		*vec;
	size_t		len;
	size_t		cnt;
}				t_table;

t_table			*new_table(size_t len);
t_entry			*delete_from_table(t_table *t, t_entry *kv);
uint32_t		do_hash(char *str, size_t len, uint32_t seed);
uint32_t		insert_into_table(t_table *t, t_entry *kv);
t_entry			*lookup_into_table(t_table *t, t_entry *kv);
t_entry			*new_entry(unsigned int key, void *data);
void			*del_entry(t_entry *n);

# ifdef DEBUG_F

void			print_entry(t_entry *n);
void			print_table(t_table *t);

# endif

#endif
