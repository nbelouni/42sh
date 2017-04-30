/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bang2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 22:39:48 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/30 22:39:58 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char		*find_replace_cmd(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (is_space(s, i) || is_char(s, i, ';') || is_char(s, i, '|') ||
		is_char(s, i, '<') || is_char(s, i, '>') || is_char(s, i, '&'))
			return (ft_strsub(s, 0, i));
		i++;
	}
	return (ft_strdup(s));
}

char	*ft_gets_lastcmd(t_lst *hist)
{
	char	*ret;

	ret = NULL;
	if (hist == NULL)
		return (NULL);
	if (hist->tail == NULL)
		return (NULL);
	if (hist->tail->name == NULL)
		return (NULL);
	if ((ret = ft_strdup(hist->tail->name)) == NULL)
		return (NULL);
	return (ret);
}

char	*ft_gets_hist_ncmd(t_lst *hist, int n)
{
	char	*ret;
	t_elem	*tmp;

	ret = NULL;
	if ((tmp = ft_get_nelem(hist, n)) == NULL)
		return (NULL);
	if (tmp->name == NULL)
		return (NULL);
	if ((ret = ft_strdup(tmp->name)) == NULL)
		return (NULL);
	return (ret);
}

char	*ft_gets_quicksub(t_lst *hist, char *search, char *replace)
{
	char	*ret;
	char	*orig;

	ret = NULL;
	if ((orig = ft_gets_lastcmd(hist)) == NULL)
	{
		return (NULL);
	}
	if (search == NULL || search[0] == '\0')
	{
		return (NULL);
	}
	ret = ft_strreplace(orig, search, replace);
	ft_strdel(&orig);
	return (ret);
}

char	*ft_gets_until_now(char *s, char *ptr)
{
	char	*buf;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (s[++i] != ptr[0])
		++j;
	if (j != 0)
	{		
		if ((buf = ft_strnew(j)) == NULL)
			return (NULL);
		ft_strncpy(buf, s, (ft_strlen(s) - ft_strlen(ptr)));
	}
	else
	{
		if ((buf = ft_strdup("")) == NULL)
			return (NULL);
	}
	return (buf);
}

