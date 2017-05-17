/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 14:45:01 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 20:38:52 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	env_remove_var(t_env *env, size_t key_index)
{
	size_t environ_size;
	char	**environ;
	char	**new_environ;

	environ = env->environ;
	environ_size = env->environ_size;
	new_environ = palloc(sizeof(char*) * (environ_size - 1 + 1), __func__);
	free(environ[key_index]);
	ft_addcpy((void**)new_environ, (const void**)environ, key_index);
	ft_addcpy((void**)new_environ + key_index, \
			(const void**)environ + key_index + 1, environ_size - key_index);
	new_environ[environ_size - 1] = NULL;
	free(env->environ);
	env->environ = new_environ;
	env->environ_size--;
}
