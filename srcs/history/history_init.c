/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:17 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

t_hist	*singleton_hist(void)
{
	static t_hist	h;

	return (&h);
}

void	history_init(t_hist *h)
{
	h->cur = NULL;
}
