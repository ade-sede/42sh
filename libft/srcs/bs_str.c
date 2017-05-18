/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bs_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 11:35:00 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 15:16:08 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

short int bs_str(const char *str, int i, char c)
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
