/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:55:31 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/13 14:18:00 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <stdio.h>

static int	update_pwd_old_pwd(char *cwd_before_chdir)
{
	char	buf[PATH_MAX];
	t_env	*env;

	env = singleton_env();
	env_add_change(env, "PWD", (const char*)getcwd(buf, PATH_MAX));
	env_add_change(env, "OLDPWD", (const char*)cwd_before_chdir);
	free(cwd_before_chdir);
	return (EXIT_SUCCESS);
}

int			builtin_cd(t_env *env, const char **argv)
{
	char	buf[PATH_MAX];
	char	*cwd_before_chdir;
	char	*new_pwd;

	if (ft_arraylen(argv) == 1)
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "HOME", NULL)))
			return (return_failure(NULL, "cd: HOME not set"));
	}
	else if (ft_strequ(argv[1], "-"))
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "OLDPWD", NULL)))
			return (return_failure(NULL, "cd: OLDPWD not set"));
	}
	else
		new_pwd = (char*)argv[1];
	ft_bzero(buf, PATH_MAX);
	cwd_before_chdir = ft_strdup(getcwd(buf, PATH_MAX));
	ft_bzero(buf, PATH_MAX);
	if (chdir(new_pwd) == -1)
	{
		free(cwd_before_chdir);
		return (return_failure("cd: no such file or directory: ", new_pwd));
	}
	return (update_pwd_old_pwd(cwd_before_chdir));
}
