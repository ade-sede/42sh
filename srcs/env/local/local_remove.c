/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:56 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local.h"

int		local_remove(t_env *env, const char *key)
{
	t_list *node;

	node = local_get_node(env->local, key);
	if (node)
		ft_simple_lst_del_one(&env->local, node, free_local);
	return (1);
}
