/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 22:35:18 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/14 23:25:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "printf.h"

void		print_environ(const char **environ)
{
	while (*environ)
	{
		ft_printf("%s\n", *environ);
		environ++;
	}
}

char		**create_environ(const char **original, size_t *new_size)
{
	char	**new_environ;
	size_t	original_size;

	original_size = (original == NULL) ? 0 : ft_arraylen(original);
	new_environ = palloc(sizeof(char*) * original_size + 1, __func__);
	ft_addcpy((void**)new_environ, (const void**)original, original_size);
	new_environ[original_size] = NULL;
	if (new_size != NULL)
		*new_size = original_size;
	return (new_environ);
}

char		*ft_get_env(const char **environ, const char *key, size_t *index)
{
	size_t	i;
	size_t	key_size;

	key_size = ft_strlen(key);
	index = 0;
	while (environ[i] && ft_strncmp(key, environ[i], key_size) != 0)
		i++;
	if (index != NULL)
		*index = i;
	return ((char*)environ[i]);
}
