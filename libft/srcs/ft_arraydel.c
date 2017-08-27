/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:13 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:13:25 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arraydel(char ***tab)
{
	char	**tmp;

	tmp = *tab;
	while (*tmp)
	{
		ft_bzero(*tmp, ft_strlen(*tmp));
		ft_memdel((void*)tmp);
		tmp++;
	}
	free(*tab);
	*tab = NULL;
}
