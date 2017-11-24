/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_local.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
#include "libft.h"
#include "local.h"

t_local				*create_local(const char *key, const char *value)
{
	t_local		*local;

	if (ft_str_isdigit(key))
		return ((void*)(long)(investigate_error(1, "Wrong assignement :",
						"key cannot be fully numeric", 0)));
		local = palloc(sizeof(*local));
	local->key = ft_strdup(key);
	local->value = ft_strdup(value);
	return (local);
}

void				free_local(void *local)
{
	t_local		*node;

	node = local;
	free(node->key);
	free(node->value);
	free(node);
}
