/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_create_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 15:29:18 by nbelouni          #+#    #+#             */
/*   Updated: 2017/03/22 18:44:52 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int			print_err_message(char *s)
{
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
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
		if (prev->bt_level < 0)
			return (print_err_message(")"));
		if (prev->bc_level < 0)
			return (print_err_message("}"));
		if (is_dir_type(prev->type))
			return (print_err_message("newline"));
		if ((is_separator_type(prev->type) && prev->type != DOT) ||
		prev->bt_level > 0 || prev->bc_level > 0 ||
		prev->word[ft_strlen(prev->word) - 1] == '\\')
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
	if (tmp->type == O_BRACKET && prev && !is_separator_type(prev->type)
	&& !is_open_group_type(prev->type))
		return (print_err_message(tmp->word));
	if (tmp->type == C_BRACKET &&
	(!prev || (prev->type != DOT
	&& !is_text_type(prev->type) && !is_close_group_type(prev->type))))
		return (print_err_message(tmp->word));
	if (tmp->type == O_BRACE && prev && !is_separator_type(prev->type)
	&& !is_open_group_type(prev->type))
		return (print_err_message(tmp->word));
	if (tmp->type == C_BRACE && (!prev || prev->type != DOT))
		return (print_err_message(tmp->word));
	if (is_separator_type(tmp->type) &&
	(!prev || is_separator_type(prev->type) || is_dir_type(prev->type)
	|| is_open_group_type(prev->type)))
		return (print_err_message(tmp->word));
	if (tmp->type == CMD && prev && is_close_group_type(prev->type))
		return (print_err_message(tmp->word));
	if (is_dir_type(tmp->type) &&
	(!prev || is_separator_type(prev->type) || is_dir_type(prev->type)))
		return (print_err_message(tmp->word));
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
	if (!prev && (lst->type == O_BRACKET || lst->type == O_BRACE ||
	lst->word[ft_strlen(lst->word) - 1] == '\\'))
	{
		set_prompt(PROMPT2, ft_strlen(PROMPT2));
		return (ERR_NEW_PROMPT);
	}
	return (is_new_prompt(prev));
}
