/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 20:17:21 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/02 13:27:41 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char	**ft_env_to_tab(void)
{
	t_env	*tmp;
	char	**res;
	int		i;

	if (!(res = (char **)malloc(sizeof(char *) * (g_env->size + 1))))
	{
		return (NULL);
	}
	tmp = g_env->head;
	i = 0;
	while (tmp != NULL)
	{
		res[i] = ft_memalloc(ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2);
		res[i] = ft_strcat(tmp->name, "-");
		res[i] = ft_strcat(res[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}
