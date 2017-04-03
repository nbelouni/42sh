/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:19:58 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/22 14:43:09 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*
**	file where error defines are defined
*/

# define ERR_WARING				0
# define ERR_NEW_CMD			-1
# define ERR_EXIT				-2
# define ERR_NEW_PROMPT			-3
# define ERR_FD					-4

/*
** System errors
*/

# define ERR_MALLOC				": Bad allocation\n"
# define ERR_READ				": Input error\n"

# define ERR_OPTION				": illegal option"

# define ERR_NUM_ARG			": numeric argument required"
# define ERR_EXT_FRMT			": Badly formed number"
# define ERR_NO_FILE			": No such file or directory"
# define ERR_EXPR_SYNT			": Expression Syntax"
# define ERR_NO_ACCESS			": Permission denied"
# define ERR_ARG_INVALID		": Invalid argument"
# define ERR_VAR_NO_ALPHA		": Varname must contain alphanumeric characters"
# define ERR_TOO_FEW_ARGS		": Too few arguments"
# define ERR_TOO_MANY_ARGS		": Too many arguments"
# define ERR_VAR_BEG_NO_ALPHA	": Variable name must begin with a letter"
# define ERR_STR_NOT_IN_PWD		": string not in pwd"
# define ERR_HOME_NOT_SET		": HOME not set"
# define ERR_OLDPWD_NOT_SET		": OLDPWD not set"
# define ERR_CMD_TOO_LONG		": command too long"
# define ERR_FD_AMB				": ambigous redirect"
# define ERR_EVENT_NFOUND		": event not found"
# define ERR_SUBSTITUTION		": substitution failed"

#endif
