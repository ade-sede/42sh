/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 16:23:39 by ade-sede         ###   ########.fr       */
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
