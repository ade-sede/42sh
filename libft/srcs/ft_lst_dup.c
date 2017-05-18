/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:24:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/18 17:25:08 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_simple_lst_dup(t_list **new_list_first, t_list *original)
{
	t_list	*new_node;

	new_node = NULL;
	while (original)
	{
		new_node = ft_simple_lst_create(original->data);
		if (!(*new_list_first))
			*new_list_first = new_node;
		else
			ft_simple_lst_pushback(new_list_first, new_node);
		original = original->next;
	}
}
