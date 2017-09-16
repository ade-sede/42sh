/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 02:10:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:10:24 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

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
