/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 22:35:18 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/15 11:57:05 by ade-sede         ###   ########.fr       */
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
	char		**new_environ;
	size_t	original_size;

	original_size = (original == NULL) ? 0 : ft_arraylen(original);
	new_environ = ft_arraydup(original);
	if (new_size != NULL)
		*new_size = original_size;
	return (new_environ);
}

char		*ft_get_env(const char **environ, const char *key, size_t *index)
{
	size_t	i;
	size_t	key_size;
	char		*value;

	key_size = ft_strlen(key);
	i = 0;
	while (environ[i] && ft_strncmp(key, environ[i], key_size) != 0)
		i++;
	if (index != NULL)
		*index = i;
	if (environ[i])
		value = (char*)(environ[i] + ft_strichr((char*)environ[i], '=') + 1);
	else
		value = NULL;
	return (value);
}
