/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "array.h"
#include "env.h"
#include "hash_table.h"

t_env	*singleton_env(void)
{
	static t_env	env;

	return (&env);
}

int		env_copy_env(t_env *new_env, t_env *old_env)
{
	if (!new_env || !old_env)
		return (0);
	new_env->environ = NULL;
	new_env->previous_exit = old_env->previous_exit;
	new_env->environ = env_create_environ((const char **)old_env->environ, \
			&(new_env)->environ_size);
	new_env->hash_table = NULL;
	return (1);
}

int		env_free_env(t_env *env)
{
	if (!env)
		return (0);
	free_hash_table(&env->hash_table);
	env->hash_table = NULL;
	ft_arraydel(&(env->environ));
	return (1);
}
