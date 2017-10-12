/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_get_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local.h"

char	*local_get_var(t_list *local, char *key_want)
{
	char	*key;

	while (local != NULL)
	{
		key = key_of_local(local->data, '=');
		if (ft_strcmp(key_want, key) == 0)
		{
			free(key);
			return (value_of_local(local->data, '='));
		}
		free(key);
		local = local->next;
	}
	return (NULL);
}
