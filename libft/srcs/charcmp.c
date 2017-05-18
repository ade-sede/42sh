/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 13:55:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 15:38:38 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	charcmp(const char *str, int index, char *char_base)
{
	int	ret;
	ret = false;

	ft_putchar(10);
	if (ft_strichr(char_base, str[index]) == -1)
		return (false); 
	while (index && str[index - 1] == '\\')
	{
		ret = (!ret) ? true : false;
		index--;
	}
	if (ret)
		return (false);
	return (true);
}
