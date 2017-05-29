/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraychr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 16:45:48 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/29 16:47:30 by ade-sede         ###   ########.fr       */
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
