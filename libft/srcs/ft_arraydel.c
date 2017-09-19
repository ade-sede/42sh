/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:36 by ade-sede         ###   ########.fr       */
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
