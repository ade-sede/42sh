/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_local.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:49 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/23 15:05:16 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local.h"

static t_list	*find_key(t_list *local, char *new_data)
{
	char	*new_key;
	char	*key;

	new_key = key_of_local(new_data, '=');
	while (local)
	{
		key = key_of_local(local->data, '=');
		if (ft_strcmp(new_key, key) == 0)
		{
			free(new_key);
			free(key);
			return (local);
		}
		free(key);
		local = local->next;
	}
	free(new_key);
	return (NULL);
}

int				add_to_local(t_list **local, char *data)
{
	t_list	*match_key;
	
	if ((match_key = find_key(*local, data)) == NULL)
		ft_simple_lst_pushback(local, ft_simple_lst_create(data));
	else
		match_key->data = ft_strchange(match_key->data, data);
	return (0);
}
