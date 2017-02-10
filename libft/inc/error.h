/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:19:58 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/09 19:21:00 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
**	file where error defines are defined
*/

# define ERR_WARNING		0
# define ERR_NEW_CMD		-1
# define ERR_EXIT			-2

/*
** System errors
*/
# define ERR_MALLOC			": Bad allocation\n"
# define ERR_READ			": Input error\n"

/*
**
*/
# define ERR_NB_ARGS		": too many arguments\n"
# define ERR_EXPR_SYNT		": Expression Syntax\n"
# define ERR_NO_ACCESS		": No Access\n"
# define ERR_NO_FILE		": No File\n"

/*
** line edition errors
*/
# define ERR_CMD_TOO_LONG	": Command too long\n"


#endif
