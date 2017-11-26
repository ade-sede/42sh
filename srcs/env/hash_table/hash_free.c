/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hash_table.h"
#include "t_env.h"

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
