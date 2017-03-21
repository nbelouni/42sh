/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bang.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:32:23 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/21 19:49:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

char		*find_number(char *s)
{
	int		i;

	i = 0;
	if (s[i] > '9' || s[i] < '0')
		return (NULL);
	if (s[0] == '-')
		i += 1;
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

char	*ft_gets_firstword(char *str)
{
	int		len;
	char	*ret;
	char	*ptr;

	ret = NULL;
	if ((ptr = ft_strchr(str, ' ')) == NULL)
	{
		if ((ret = ft_strdup(str)) == NULL)
			return (NULL);
	}
	else
	{
		len = ft_strlen(str) - ft_strlen(ptr);
		if ((ret = ft_strnew(len)) == NULL)
			return (NULL);
		ret = ft_strncpy(ret, str, len);
	}
	return (ret);
}

char	*ft_gets_lastword(char *str)
{
	char	*ret;
	char	*ptr;
	char	*tmp;

	ret = NULL;
	tmp = ft_strtrim(str);
	if ((ptr = ft_strrchr(tmp, ' ')) == NULL)
	{
		if ((ret = ft_strdup(tmp)) == NULL)
		{
			ft_strdel(&tmp);
			return (NULL);
		}
	}
	else
	{
		++ptr;
		if ((ret = ft_strdup(ptr)) == NULL)
		{
			ft_strdel(&tmp);
			return (NULL);
		}
	}
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

/*int main(void)
{
	t_lst *hist;
	t_lst *set;
	char	*res;
	char	*cmd = "je fais des tests    ";

	hist = NULL;
	set = NULL;
	ft_histopt_r(&hist, set, ".42sh_history");
	// ft_print_history(hist, hist->size);
	res = ft_gets_lastword(cmd);
	ft_putendl(res);
	// res = ft_gets_in_hist(hist, cmd, ft_strncmp_int);
	// ft_putendl(res);

return (0);	
}
*/
// int		ft_check_expansion_type(char *s)
// {
// 	if (s[0] == '!')
// 	{
// 		if (s[1] == '\0')
// 			return (ft_print_error("bash: ", ERR_EXPR_SYNT))
// 		if (s[1] == '!')
// 			return ((s[2] != '\0') ? DOUBLE_BANG : -1);
// 		else if (ft_isdigit(s[1]))
// 			return (N_BANG);
// 		else if (s[1] == '-' && ft_isdigit(s[2]))
// 			return (N_LESS_BANG);
// 		else if (s[1] != '?' && !ft_isdigit(s[1]))
// 			return (ft_strstr(&s[2], ":p") ? PRINT_SSTART_BANG : SSTART_BANG);
// 		else if (s[1] == '?')
// 			return (STR_CONTAIN_BANG);
// 		else if (s[1] == '#')
// 			return (UNTIL_NOW_BANG);
// 		else if (s[1] == '$')
// 			return (ft_strstr(&s[2], ":p") ? PRINT_LAST_BANG : RUN_LAST_BANG);
// 		else if (s[1] == '*')
// 			return (ft_strstr(&s[2], ":p") ? PRINT_EXCEPT_FIRST_BANG : \
// 				RUN_EXCEPT_FIRST_BANG);
// 	}
// 	if (s[0] == '^')
// 		return (QUICK_SUB);
// 	return (-1);
// }

// char	*ft_builtin_expansion(t_lst *hist, char *cmd, int type)
// {
// 	char	*res;
// 	int		calc;t_elem	*elem;

// 	res = NULL;
// 	if (hist != NULL && hist->head != NULL)
// 	{
// 		if (type == DOUBLE_BANG)
// 			res = hist->tail->name;
// 		else if (type == N_BANG || type == N_LESS_BANG)
// 		{
// 			calc = (type == N_BANG) ? ft_atoi(&cmd[1]) : (hist->size - ft_atoi(&cmd[2]));
// 			if ((elem = ft_get_nelem(hist, calc)) == NULL)
// 				ft_print_error(cmd, ERR_EVENT_NFOUND, 0);
// 			res = (elem != NULL) ? elem->name : NULL;
// 		}
// 		else if (type == STR_START_BANG || STR_CONTAIN_BANG)
// 		{
// 			if (type == STR_START_BANG)
// 			{
// 	
// 				;
// 			}
// 		}
// 	}
// 	return (res);
// }
