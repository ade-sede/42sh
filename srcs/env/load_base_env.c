/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_base_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:09 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "printf.h"
#include "hash_table.h"

void		env_load_base_env(t_env *env, const char **environ)
{
	env->environ = NULL;
	env->previous_exit = 0;
	env->alias = NULL;
	env->environ = env_create_environ(environ, &(env->environ_size));
	env_load_shlvl_pwd(env);
	create_hash_table(env);
}

void		env_load_shlvl_pwd(t_env *env)
{
	char		buf[PATH_MAX];
	size_t		index;
	char		*new_entry;

	if (env_getenv((const char**)env->environ, "PWD", &index) == NULL)
		env_add_var(env, "PWD", getcwd(buf, PATH_MAX));
	if (env_getenv((const char **)env->environ, "SHLVL", &index) == NULL)
		env_add_var(env, "SHLVL", "1");
	else
	{
		new_entry = ft_itoa_base(ft_atoi((env->environ)[index] + 6) + 1, 10);
		env_change_value(env, "SHLVL", index, new_entry);
		free(new_entry);
	}
	env_add_change(env, "SHELL", "21sh");
	env_add_change(env, "HISTFILE", ".21sh_history");
}
