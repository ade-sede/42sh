/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:24:14 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/26 21:24:16 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_last_simple_lst(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_previous_last_simple_lst(t_list *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst && lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}
