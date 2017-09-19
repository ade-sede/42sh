/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:58 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new_str;
	int		i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	if ((new_str = (char*)malloc(ft_strlen(s) + 1)) == NULL)
		return (NULL);
	while (s[i])
	{
		new_str[i] = (*f)(s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
