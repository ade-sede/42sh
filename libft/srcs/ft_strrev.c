/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:36:26 by ade-sede          #+#    #+#             */
/*   Updated: 2016/11/14 13:50:09 by ade-sede         ###   ########.fr       */
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
