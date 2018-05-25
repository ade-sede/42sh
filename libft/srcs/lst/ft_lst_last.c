/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_last_simple_lst(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	*ft_genlst_last(void *lst)
{
	t_gen_lst	*lst_cast;

	lst_cast = lst;
	while (lst_cast && lst_cast->next)
		lst_cast = lst_cast->next;
	return (lst_cast);
}

t_list	*ft_previous_last_simple_lst(t_list *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst && lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}
