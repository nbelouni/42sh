/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:12:03 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:12:38 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# define CD_OPT				"LP"
# define ENV_OPT			"i"
# define UNSET_OPT			"fv"
# define EXPORT_OPT			"p"
# define HIST_OPTS			"cpsdanrw"

# define HIST_OPT_C			99
# define HIST_OPT_P			112
# define HIST_OPT_S			115
# define HIST_OPT_D			100
# define HIST_OPT_A			97
# define HIST_OPT_N			110
# define HIST_OPT_R			114
# define HIST_OPT_W			119

/*
**	ft_opt_parse.c
*/

int		*ft_opt_parse(char *opts, char **av, int overwrite, int print_o);

#endif
