/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraychr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:13 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:13:24 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "libft.h"
#include "str.h"

const char	**ft_arraychr(const char **array, const char *str)
{
	if (!array || !str)
		return (NULL);
	while (*array && !ft_strequ(*array, str))
		array++;
	if (*array)
		return (array);
	return (NULL);
}
