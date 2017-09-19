/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:49 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:18 by ade-sede         ###   ########.fr       */
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
