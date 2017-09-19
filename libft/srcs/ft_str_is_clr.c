/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_clr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:52 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "libft.h"

int		ft_str_is_clr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}
