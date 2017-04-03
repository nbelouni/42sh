/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bang.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:32:23 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/24 17:42:42 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char		*find_number(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '-')
		i += 1;
	if (!ft_isdigit(s[i]))
		return (NULL);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (ft_strsub(s, 0, i));
		i++;
	}
	if (s[i - 1] < '9' && s[i - 1] > '0')
		return (ft_strdup(s));
	return (NULL);
}

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

char	*ft_gets_cmd_except_firstword(char *str)
{
	char	*ptr;
	char	*ret;
	char	*tmp;

	if ((tmp = ft_strtrim(str)) == NULL)
	{
		return (NULL);
	}
	ptr = ft_strchr(tmp, ' ');
	ret = (ptr == NULL) ? "" : ft_strtrim(ptr);
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
	// if ((ptr = ft_strrchr(tmp, ' ')) == NULL)
	// {
	// 	ret = ft_strdup(tmp);
	// }
	// else
	// {
	// 	++ptr;
	// 	ret = ft_strdup(ptr);
	// }
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
