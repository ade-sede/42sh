/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:41:23 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:41:40 by vcombey          ###   ########.fr       */
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
