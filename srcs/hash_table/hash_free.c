/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:12 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "hash_table.h"
#include "env.h"

void	free_hash_table(t_list **hash_table)
{
	t_list	*tmp;
	t_list	*elem;
	size_t	i;

	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		elem = hash_table[i];
		while (elem)
		{
			tmp = elem->next;
			ft_strdel((char **)&elem->data);
			free(elem);
			elem = tmp;
		}
		hash_table[i] = NULL;
		i++;
	}
	free(hash_table);
}
