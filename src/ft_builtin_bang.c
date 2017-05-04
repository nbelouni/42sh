/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bang.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:08:31 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/04 16:13:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char	*ft_gets_cmd_except_firstword(char *str)
{
	char	*ptr;
	char	*ret;
	char	*tmp;

	if ((tmp = ft_strtrim(str)) == NULL)
	{
		return (NULL);
	}
	if ((ptr = ft_strrchr(tmp, ' ')))
	{
		ret = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(ptr));
	}
	else
	{
		ret = ft_strdup("");
	}
	ft_strdel(&tmp);
	return (ret);
}

char	*ft_gets_lastword(char *str)
{
	char	*ret;
	char	*ptr;
	char	*tmp;

	ret = NULL;
	if ((tmp = ft_strtrim(str)) == NULL)
		return (NULL);
	ptr = ft_strrchr(tmp, ' ');
	ret = (ptr != NULL) ? ft_strdup(&(ptr[1])) : ft_strdup(tmp);
	ft_strdel(&tmp);
	return (ret);
}

int		ft_strstr_bis(char *s1, char *s2, int n)
{
	(void)n;
	if (ft_strstr(s1, s2) != NULL)
	{
		return (0);
	}
	return (-1);
}

int		ft_strncmp_bis(char *s1, char *s2, int n)
{
	if (ft_strncmp(s1, s2, n) == 0)
		return (0);
	return (-1);
}

char	*ft_gets_in_hist(t_lst *hist, char *s, int (*f)(char *, char *, int))
{
	char	*ret;
	t_elem	*tmp;

	ret = NULL;
	tmp = hist->tail;
	while (tmp != NULL)
	{
		if (tmp->name != NULL && tmp->name[0] != '\0')
		{
			if (f(tmp->name, s, (int)ft_strlen(s)) == 0)
			{
				if ((ret = ft_strdup(tmp->name)) == NULL)
					return (NULL);
				break ;
			}
		}
		tmp = tmp->prev;
	}
	return (ret);
}
