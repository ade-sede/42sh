/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_base_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "printf.h"
#include "hash_table.h"
#include "local.h"

void		env_load_base_env(t_env *env, const char **environ)
{
	size_t	i;

	i = 0;
	env->environ = NULL;
	env->previous_exit = 0;
	env->option = 0;
	env->alias = NULL;
	env->local = NULL;
	env->environ = env_create_environ(environ, &(env->environ_size));
	env_load_shlvl_pwd(env);
	if (0)
		while (i != env->environ_size)
		{
			add_to_local(&env->local, ft_strdup(env->environ[i]));
			++i;
		}
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
