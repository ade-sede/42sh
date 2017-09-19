/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_refresh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:49 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:19 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void	history_refresh_command(t_hist *h, char *command)
{
	write(h->fd, command, ft_strlen(command));
	write(h->fd, "\n", 1);
}

void	history_write_last_command(void)
{
	t_hist		*h;
	t_list_d	*list;

	h = singleton_hist();
	list = h->list->first;
	history_refresh_command(h, list->data);
}

void	history_refresh(char *command)
{
	t_hist		*h;
	t_list_d	*list;

	h = singleton_hist();
	if (command[0] == '\0' || ft_str_is_clr(command))
		return ;
	list = ft_double_lst_create(ft_strdup(command));
	if (h->list == NULL)
		h->list = ft_create_head(list);
	else
		ft_double_lst_add(&h->list, list);
}
