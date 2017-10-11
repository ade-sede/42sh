/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:41:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:41 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

short int	charcmp(const char *str, size_t i, char c)
{
	int ret;

	ret = FALSE;
	if (str[i] != c)
		return (FALSE);
	else
		while (i != 0 && str[i - 1] == '\\')
		{
			i--;
			ret = (ret) ? 0 : 1;
		}
	if (ret)
		return (FALSE);
	return (TRUE);
}
