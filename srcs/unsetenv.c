/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:45:01 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/15 17:49:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char		**remove_var(char **environ, size_t environ_size, size_t key_index)
{
	char	**new_environ;

	new_environ = palloc(sizeof(char*) * (environ_size - 1 + 1), __func__);
	ft_addcpy((void**)new_environ, (const void**)environ, key_index);
	ft_addcpy((void**)new_environ + key_index, \
			(const void**)environ + key_index + 1, environ_size - key_index);
	new_environ[environ_size - 1] = NULL;
	return (new_environ);
}
