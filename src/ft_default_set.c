#include "42sh.h"

t_lst	*ft_init_lstset(void)
{
	t_lst *set;
	char	*pwd;
	char	*histfilepath;

	pwd = NULL;
	histfilepath = NULL;
	set = NULL;
	if ((set = ft_init_list()) == NULL)
		return (NULL);
	if ((pwd = getcwd(NULL, PATH_MAX)) == NULL)
	{
		free(set);
		return (NULL);
	}
	if ((histfilepath = ft_strnew((ft_strlen(pwd) + 15))) == NULL)
		return (NULL);
	ft_strcpy(histfilepath, pwd);
	histfilepath = ft_strcat(histfilepath, "/.42sh_history");
	ft_setenv(set, "HISTFILE", histfilepath);
	ft_multi_free(pwd, histfilepath, NULL, NULL);
	ft_setenv(set, "HISTSIZE", "500");
	ft_setenv(set, "HISTFILESIZE", "500");
	return (set);
}