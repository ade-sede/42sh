/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 13:41:21 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 14:49:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char		**add_var(char **environ, size_t environ_size, const char* new_value)
{
	char		**new_environ;
	size_t	new_environ_size;

	new_environ_size = environ_size + 1;
	new_environ = palloc(sizeof(char*) * new_environ_size + 1, __func__);
	ft_addcpy((void**)new_environ, (const void**)environ, environ_size);
	new_environ[new_environ_size - 1] = ft_strdup(new_value);
	new_environ[new_environ_size] = NULL;
	return (new_environ);
}

void		change_value(char **environ, char *key, size_t key_index, char* new_value)
{
	free(environ[key_index]);
	environ[key_index] = ft_strsurround(key, "=", new_value);
}
