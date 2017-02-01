#include "42sh.h"

char	**ft_env_to_tab(void)
{
	t_elem	*tmp;
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
	}
	res[i] = NULL;
	return (res);
}
