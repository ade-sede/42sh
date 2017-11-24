/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:58 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lst_len(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

size_t	ft_genlst_len(void *lst)
{
	t_gen_lst	*lst_cast;
	int			i;

	i = 0;
	lst_cast = lst;
	while (lst_cast)
	{
		lst_cast = lst_cast->next;
		i++;
	}
	return (i);
}
