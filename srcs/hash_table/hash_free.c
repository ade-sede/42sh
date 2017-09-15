/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "hash_table.h"
#include "env.h"

void	free_hash_table(t_list ***hash_table)
{
	t_list	*tmp;
	t_list	*elem;
	size_t	i;
	t_list	**table;

	table = *hash_table;
	if (!table)
		return ;
	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		elem = table[i];
		while (elem)
		{
			tmp = elem->next;
			ft_strdel((char **)&elem->data);
			free(elem);
			elem = tmp;
		}
		table[i] = NULL;
		i++;
	}
	free(*hash_table);
	*hash_table = NULL;
}
