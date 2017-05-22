/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 13:55:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/22 12:05:43 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

short int	charcmp(const char *str, size_t i, char c)
{
	int ret;

	ret = false;
	if (str[i] != c)
		return (false);
	else
		while (i != 0 && str[i - 1] == '\\')
		{
			i--;
			ret = (ret) ? 0 : 1;
		}
	if (ret)
		return (false);
	return (true);
}


