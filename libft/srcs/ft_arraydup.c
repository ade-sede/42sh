/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:13 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:13:26 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "str.h"
#include "alloc.h"
#include "libft.h"

char	**ft_arraydup(const char **original)
{
	char	**new_environ;
	size_t	original_size;
	size_t	i;

	i = 0;
	original_size = (original == NULL) ? 0 : ft_arraylen(original);
	new_environ = palloc(sizeof(char*) * (original_size + 1));
	while (i != original_size)
	{
		new_environ[i] = ft_strdup(original[i]);
		i++;
	}
	new_environ[original_size] = NULL;
	return (new_environ);
}
