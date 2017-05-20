/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:31:30 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/20 19:36:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "env.h"
#include "libft.h"


void	env_remove_var_index(t_env *env, size_t key_index)
{
	size_t environ_size;
	char	**environ;
	char	**new_environ;

	environ = env->environ;
	environ_size = env->environ_size;
	new_environ = palloc(sizeof(char*) * (environ_size - 1 + 1), __func__);
	free(environ[key_index]);
	ft_addrcpy((void**)new_environ, (const void**)environ, key_index);
	ft_addrcpy((void**)new_environ + key_index, \
			(const void**)environ + key_index + 1, environ_size - key_index);
	new_environ[environ_size - 1] = NULL;
	free(env->environ);
	env->environ = new_environ;
	env->environ_size--;
}


void	env_remove_var(t_env *env, const char *key)
{
	size_t	index;

	if (env_getenv((const char**)env->environ, key, &index))
		env_remove_var_index(env, index);
}
