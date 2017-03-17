/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_histopt_offset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:59:42 by maissa-b          #+#    #+#             */
/*   Updated: 2017/03/14 15:38:45 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		ft_del_hist_offset(t_lst *hist, char *arg)
{
	t_elem	*tmp;
	int		offset;

	offset = ft_atoi(arg);
	if (offset <= 0 || offset > (int)hist->size)
	{
		write(2, "history: ", 9);
		return (ft_print_error(arg, ": position out of range", ERR_NEW_CMD));
	}
	tmp = ft_get_nelem(hist, offset);
	ft_del_elem(&tmp, hist);
	return (0);
}

int		ft_histopt_d(t_lst *hist, char *arg)
{
	if (arg == NULL || *arg == '\0')
	{
		return (ft_print_error("history", ": usage -d <n>", ERR_NEW_CMD));
	}
	if (ft_del_hist_offset(hist, arg) == ERR_NEW_CMD)
	{
		return (ERR_NEW_CMD);
	}
	return (0);
}
