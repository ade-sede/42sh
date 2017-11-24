/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:56 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_env.h"

t_list			*local_get_node(t_list *first, const char *key)
{
	t_local		*tmp;

	while (first)
	{
		tmp = first->data;
		if (ft_strequ(key, tmp->key))
			return (first);
		first = first->next;
	}
	return (NULL);
}

char			*local_get_value(t_list *first, const char *key)
{
	t_list		*node;
	t_local		*local;

	node = local_get_node(first, key);
	if (!node)
		return (NULL);
	local = node->data;
	return (local->value);
}

char			*get_pos_param_value(t_list *pos_param, int key)
{
	t_pos_param	*node;

	while (pos_param)
	{
		node = pos_param->data;
		if (node->key == key)
			break ;
		pos_param = pos_param->next;
	}
	if (!pos_param)
		return (NULL);
	return (node->value);
}

char			*var_get_value(t_env *env, const char *key)
{
	char		*ret;

	ret = local_get_value(env->local, key);
	if (!ret && ft_str_isdigit(key))
		ret = get_pos_param_value(env->pos_param, ft_atoi_base((char*)key, 10));
	return (ret);
}
