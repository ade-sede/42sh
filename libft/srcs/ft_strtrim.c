/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:02:33 by ade-sede          #+#    #+#             */
/*   Updated: 2016/11/13 17:56:34 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_char_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL || (new_str = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	while (i != ft_strlen(s))
	{
		if (ft_char_is_space(s[i]) && !j)
			i++;
		else
			new_str[j++] = s[i++];
	}
	while (ft_char_is_space(new_str[--j]))
		new_str[j] = '\0';
	return (new_str);
}
