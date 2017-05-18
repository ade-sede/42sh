/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnreplace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 19:29:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/06 19:33:16 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strnreplace(char *str, char target, char replace, int size)
{
	int		i;

	i = 0;
	while (i != size)
	{
		if (str[i] == target)
			str[i] = replace;
		i++;
	}
}
