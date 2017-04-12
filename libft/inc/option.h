/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:21:14 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/10 07:33:01 by llaffile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

# include <ctype.h>

# define NOT_OPT 63
# define NO_ARG 58
# define ERR_ILLEGAL_OPT "illegal option -- "
# define NOT_ARG_ERRSTR ": option require an argument.\n"
# define RESET ""

typedef struct	s_opt
{
	int			opt_ind;
	int			opt_res;
	int			opt_char;
	char		*opt_arg;
}				t_opt;

int				ft_getopt(int argc, char **argv, char *optstr, t_opt *st_opt);
void			init_optstruct(t_opt *opt_struct);

#endif
