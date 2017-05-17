/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 18:07:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 20:49:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	builtin_cd(t_env *env, char **argv)
{
	char buf[PATH_MAX];
	char	*current_pwd;
	char	*new_pwd;

	if (ft_arraylen((const char**)argv))
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "HOME", NULL)))
			return (return_failure(NULL, "cd: HOME not set"));
	}
	else if (ft_strequ(argv[1], "-"))
	{
		if (!(new_pwd = env_getenv((const char**)env->environ, "OLDPWD", NULL)))
			return (return_failure(NULL,"cd: OLDPWD not set"));
	}
	else
		new_pwd = argv[1];
	current_pwd = getcwd(buf, PATH_MAX);
	if (chdir(new_pwd) == -1)
		return(return_failure("cd: no such file or directory: ", new_pwd));
	ft_bzero(buf, PATH_MAX);
	env_add_to_env(env, "PWD", (const char*)getcwd(buf, PATH_MAX));
	env_add_to_env(env, "OLDPWD", (const char*)current_pwd);
	return (EXIT_SUCCESS);
}
