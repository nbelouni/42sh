#include "libft.h"

int		is_valid_dir(const char *dirname)
{
	DIR			*dir;
	struct stat st;
	int			ret;

	lstat(dirname, &st);
	if (S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode))
	{
		if ((dir = opendir(dirname)))
		{
			closedir(dir);
			return (0);
		}
		return (ft_print_error("cd", ERR_NO_ACCESS));
	}
	else
	{
		return (ft_print_error("cd", ERR_NO_FILE));
	}
}
