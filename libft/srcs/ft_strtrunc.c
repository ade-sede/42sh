/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 14:06:57 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/02 11:16:15 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtrunc(char **str, int size_left)
{
	int		i;
	int		j;

	j = 0;
	i = (int)ft_strlen(*str);
	while (j != size_left)
	{
		(*str)++;
		j++;
	}
	ft_bzero(*str, i - j);
}
