/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

/*
**	Looks for the very last occurence of the nul terminated string little in
**	the nul terminated string big.
*/

char				*ft_strrstr(const char *big, const char *little)
{
	const char	*found;
	const char	*tmp;
	size_t		len;

	len = ft_strlen(big);
	found = NULL;
	while ((tmp = ft_strnstr(big, little, len)))
	{
		found = tmp;
		big = tmp + 1;
	}
	return ((char*)found);
}
