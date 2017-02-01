/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/01 17:44:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*s;
	char	**array;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	line = NULL;
	while (get_next_line(0, &line))
	{
	//	ft_putendl(line);
		i = -1;
		array = NULL;
		while (line[++i])
		{
			if (line[i] == ' ')
				break;
		}
		s = ft_strsub(line, 0, i);
		if (i < (int)ft_strlen(line))
			array = ft_strsplit(line + i, ' ');
		ft_putendl(s);	
		i = -1;
		while(array && array[++i])
			ft_putendl(array[i]);	
//		fonction(s, array)
		free(line);
		free(s);
		if (array)
		{
			i = -1;
			while (array[++i])
				free(array[i]);
			free(array);
		}
	}
	return (0);
}
