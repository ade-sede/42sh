/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_clr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 02:10:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:10:24 by vcombey          ###   ########.fr       */
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
