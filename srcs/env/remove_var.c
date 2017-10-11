/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "local.h"
#include "hash_table.h"
#include "libft.h"

void	env_remove_var_index(t_env *env, size_t key_index)
{
	size_t	environ_size;
	char	**environ;
	char	**new_environ;

	environ = env->environ;
	environ_size = env->environ_size;
	new_environ = palloc(sizeof(char*) * (environ_size - 1 + 1));
	free(environ[key_index]);
	ft_memcpy(new_environ, environ, key_index * sizeof(*new_environ));
	ft_memcpy(new_environ + key_index, environ + key_index + 1, \
			(environ_size - key_index) * sizeof(*new_environ));
	new_environ[environ_size - 1] = NULL;
	free(env->environ);
	env->environ = new_environ;
	env->environ_size--;
}

void	env_remove_var(t_env *env, const char *key)
{
	size_t	index;

	if (env_getenv((const char**)env->environ, key, &index))
	{
		env_remove_var_index(env, index);
		remove_var_from_local(&env->local, (char*)key);
	}
}
