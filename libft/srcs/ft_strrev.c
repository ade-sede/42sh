/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if ((new_str = ft_strnew(ft_strlen(str) + 1)) == NULL || str == NULL)
		return (NULL);
	i = ft_strlen(str);
	j = 0;
	while (i > 0)
		new_str[j++] = str[--i];
	return (new_str);
}
