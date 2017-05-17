/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_base_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:17:42 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 20:48:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "printf.h"

void		env_load_base_env(t_env *env, const char **environ)
{
	size_t	index;
	char		*path;

	env->environ = NULL;
	env->path = NULL;
	env->environ = env_create_environ(environ, &(env->environ_size));
	env_load_shlvl_pwd(env);
	if (env_getenv((const char**)env->environ, "SHELL", &index) != NULL)
		env_change_value(env, "SHELL", index, "minishell");
	if ((path = env_getenv((const char**)env->environ, "PATH", NULL)) != NULL)
		env_create_path_list(path, &(env->path));
}

void		env_load_shlvl_pwd(t_env *env)
{
	char	buf[PATH_MAX];
	size_t	index;
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
}
