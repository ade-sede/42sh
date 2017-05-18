/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:35:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/15 11:53:40 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dest;

	if (!s1 || *s1 == '\0')
		return (NULL);
	i = 0;
	if ((dest = malloc(sizeof(char) * (ft_strlen(s1) + 1))) == NULL)
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_arraydup(const char **original)
{
	char	**new_environ;
	size_t	original_size;
	size_t	i;

	i = 0;
	original_size = (original == NULL) ? 0 : ft_arraylen(original);
	new_environ = palloc(sizeof(char*) * original_size + 1, __func__);
	while (i != original_size)
	{
		new_environ[i] = ft_strdup(original[i]);
		i++;
	}
	new_environ[original_size] = NULL;
	return (new_environ);
}
