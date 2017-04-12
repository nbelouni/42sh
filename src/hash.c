/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 20:06:57 by llaffile          #+#    #+#             */
/*   Updated: 2017/03/29 17:30:21 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

t_table *new_table(size_t len)
{
	t_table *t;

	t = malloc(sizeof(t_table));
	bzero(t, sizeof(t_table));
	t->len = len;
	t->cnt = 0;
	HASH(t) = malloc(len * sizeof(*HASH(t)));
	bzero(HASH(t), LEN(t) * sizeof(*HASH(t)));
	return (t);
}

uint32_t do_hash(char *str, size_t len, uint32_t seed)
{
	uint32_t hash;
	int		i;
	
	hash = seed;
	i = 0;
	while (i < (int)len)
	{
		hash ^= str[i] + (hash << 5 ^ hash >> 2);
		++i;
	}
	return (hash);
}

uint32_t	insert_into_table(t_table *t, t_entry *kv)
{
	uint32_t	h;

	h = GETPOS(kv, t);
	PUSH(HASH(t) + h, kv);
	//SLIST_INSERT_HEAD(HASH(t) + h, kv, sibl);
	return (h);
}
/*

# define ENTRY(k, v)	((t_entry){.key = k; .data = v})
# define VALUE(t, k)	(getDataFromTable(t, &ENTRY(k, NULL)))

void builtin(char *builtStr, void *builtParam)
{
	(VALUE(hashBuilt, builtStr))(builtParam, param2);
}

builtin("env", p1, p2, p3);

*/
void		*getDataFromTable(t_table *t, t_entry *kv)
{
	return ((lookup_into_table(t, kv))? lookup_into_table(t, kv)->data: NULL);
}

t_entry		*lookup_into_table(t_table *t, t_entry *kv)
{
	t_entry *k;
	List_p	ptr;
	uint32_t	h;

	h = GETPOS(kv, t);
	ptr = *(HASH(t) + h);
	while (ptr)
	{
		k = (t_entry *)ptr->content;
		if (strcmp(CDATA(kv), CDATA(k)) == 0)
			return (k);
		ptr = ptr->next;
	}
	return (NULL);		
}

t_entry *delete_from_table(t_table *t, t_entry *kv)
{
	t_entry		*k;
	uint32_t	h;

	k = lookup_into_table(t, kv);
	h = GETPOS(kv, t);
	if (k)
		return (remove_link_top(HASH(t) + h));
	return (NULL);
}


void print_entry(t_entry *n)
{
	printf("\t[%x][%s]\n", KEY(n), CDATA(n));
}

void print_table(t_table *t)
{
	for (int i = 0; i < (int)LEN(t); i++)
	{
		printf("[%d]:[%p]\n", i, HASH(t) + i);
		list_iter(*(HASH(t) + i), (void *)print_entry);
	}
}

t_entry *new_entry(unsigned int key, void *data)
{
	t_entry *n;

	n = malloc(sizeof(t_entry));
	n->key = key;
	n->data = data;
	return (n);
}

void *del_entry(t_entry *n)
{
	void	*data;
	
	data = n->data;
	free(n);
	return (data);
}

void del_table(t_table *t, void(f)(void *))
{
	int	i;


	i = 0;
	while (i < (int)LEN(t))
	{
		list_iter(*(HASH(t) + i), f);
		delete_list((HASH(t) + i), (void *)del_entry);
		i++;
	}
	free(t);
}

/*
void usage()
{
	printf("\tUsage:\n\n"
		"\t\t[i]-[keys] : Insert\n"
		"\t\t[l]-[keys] : Lookup\n"
		"\t\t[d]-[keys] : Delete\n"
		"\t\t[u] : usage\n"
		"\t\t[p] : print table\n"
		"\t\t[x] : exit\n");
}



int main(int argc, char **argv, char **envp)
{
	Table *t;
	char c=0;
	char str[256];
	int len;

	printf("Choose table size:\n");
	scanf("%d",&len);
	t = newTable(len);
	while (1)
	{
		usage();
		scanf("\n%c-%s",&c, str);
		printf("c:<%c>\n", c);
		switch (c)
		{
		case 'i':
		{
			Node *n = newNode(Hash(str, strlen(str), 0), strdup(str));
			printNode(n);
			if (insertIntoTable(t, n) == -1)
			{
				printf("Table is full ?\n");
				exit(EXIT_FAILURE);
			}
			printTable(t);
			break ;
		}
		case 'd':
		{
			Node *n = newNode(Hash(str, strlen(str), 0), strdup(str));
			printNode(n);
			if (deleteFromTable(t, n) == NULL)
				printf("Not in table, is it OK ?\n");
			else
				delNode(n);
			printTable(t);
			break ;
		}
		case 'l':
		{
			Node *n, *m;
			n = newNode(Hash(str, strlen(str), 0), strdup(str));
			printNode(n);
			m = lookupIntoTable(t, n);
			if (m == NULL)
				printf("Not in table, is it OK ?\n");
			else
				printNode(m);
			break ;
		}
		case 'u':
		{
			usage();
			break ;
		}
		case 'p':
		{
			printTable(t);
			break;
		}
		case 'x': exit(0);
		default: {usage();exit(0);}
		}
	}
	return (0);
}

*/
