/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:41:23 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:40 by vcombey          ###   ########.fr       */
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
