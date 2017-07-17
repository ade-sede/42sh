/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_refresh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:18 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void	history_refresh(t_line *line)
{
	t_hist		*h;
	t_list_d	*list;

	h = singleton_hist();
	list = ft_double_lst_create(ft_strdup(line->buff));
	if (h->list == NULL)
		h->list = ft_create_head(list);
	else
		ft_double_lst_add(&h->list, list); 
}
