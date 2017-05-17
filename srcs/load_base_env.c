/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_base_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:17:42 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 14:42:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "printf.h"

void		load_base_env(t_env *env, const char **environ)
{
	size_t	index;
	char		*path;

	env->environ = NULL;
	env->path = NULL;
	env->environ = create_environ(environ, &(env->environ_size));
	load_shlvl_pwd(env);
	if (ft_get_env((const char**)env->environ, "SHELL", &index) != NULL)
		change_value(env->environ, "SHELL", index, "minishell");
	if ((path = ft_get_env((const char**)env->environ, "PATH", NULL)) != NULL)
		create_path_list(path, &(env->path));
}

void		load_shlvl_pwd(t_env *env)
{
	char	buf[PATH_MAX];
	size_t	index;
	char		**new_env;
	char		*new_entry;

	if (ft_get_env((const char**)env->environ, "PWD", &index) == NULL)
	{
		new_entry = ft_strjoin("PWD=", getcwd(buf, PATH_MAX));
		new_env = add_var(env->environ, env->environ_size, new_entry);
		env->environ = (char**)ft_freeswap((t_ulong)env->environ, (t_ulong)new_env);
		free(new_entry);
		(env->environ_size)++;
	}
	if (ft_get_env((const char **)env->environ, "SHLVL", &index) == NULL)
	{
		new_env = add_var(env->environ, env->environ_size, "SHLVL=1");
		env->environ = (char**)ft_freeswap((t_ulong)env->environ, (t_ulong)new_env);
		(env->environ_size)++;
	}
	else
	{
		new_entry = ft_itoa_base(ft_atoi((env->environ)[index] + 6) + 1, 10);
		change_value(env->environ, "SHLVL", index, new_entry);
	}
}
