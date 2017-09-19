/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:15 by ade-sede         ###   ########.fr       */
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
