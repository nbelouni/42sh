/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:09:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/02 18:44:35 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H
# define FT_42SH_H

# include <stdlib.h>
# include "libft.h"

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

# include "read.h"

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct		s_manage_env
{
	t_env			*head;
	t_env			*tail;
	size_t			size;
}					t_manage_env;

t_manage_env		*g_env;

#endif