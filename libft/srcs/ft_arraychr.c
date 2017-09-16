/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraychr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 02:10:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:10:25 by vcombey          ###   ########.fr       */
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
