/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_create_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:29:18 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/07 18:56:22 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"


int			print_err_message(char *s, int token)
{
	if (token == SL_DIR)
		s = "<";
	else if (token == SR_DIR)
		s = ">";
	else if (token == DL_DIR)
		s = "<<";
	else if (token == DR_DIR)
		s = ">>";
	else if (token == LR_DIR)
		s = "<>";
	else if (token == DIR_L_AMP)
		s = "<&";
	else if (token == DIR_R_AMP)
		s = ">&";
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	if (s)
		ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	return (ERR_NEW_CMD);
}

int			is_new_prompt(t_token *prev)
{
	if (prev)
	{
		if (!(prev = prev->next))
			return (TRUE);
		if (is_dir_type(prev->type))
			return (print_err_message("newline", 0));
		if ((is_separator_type(prev->type) && prev->type != DOT) ||
	(count_prev_char(prev->word, ft_strlen(prev->word), '\\') % 2 == 1))
		{
			set_prompt(PROMPT2, ft_strlen(PROMPT2));
			return (ERR_NEW_PROMPT);
		}
		set_prompt(PROMPT1, ft_strlen(PROMPT1));
	}
	return (TRUE);
}

int			is_parse_error(t_token *tmp, t_token *prev)
{
	if (is_separator_type(tmp->type) &&
	(!prev || is_separator_type(prev->type) || is_dir_type(prev->type)))
		return (print_err_message(tmp->word, 0));
	if (is_dir_type(tmp->type) &&
	(prev && is_dir_type(prev->type)))
		return (print_err_message(tmp->word, tmp->type));
	return (0);
}

int			can_create_tree(t_token *lst)
{
	t_token	*tmp;
	t_token	*prev;
	int		ret;

	if (!lst)
		return (0);
	tmp = lst;
	prev = NULL;
	while (tmp)
	{
		prev = tmp->prev;
		if ((ret = is_parse_error(tmp, prev)))
			return (ret);
		tmp = tmp->next;
	}
	if (!prev &&
	(count_prev_char(lst->word, ft_strlen(lst->word) - 1, '\\') % 2 == 1))
	{
		set_prompt(PROMPT2, ft_strlen(PROMPT2));
		return (ERR_NEW_PROMPT);
	}
	return (is_new_prompt(prev));
}
