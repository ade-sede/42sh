/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:51:04 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/18 15:49:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int	builtin_unsetenv(t_env *env, char **argv)
{
	size_t	i;
	size_t	argc;

	argc = ft_arraylen((const char**)argv);
	if (argc == 1)
		return (return_failure("unsetenv: Too few arguments\n", NULL));
	i = 1;
	while (i < argc)
	{
		env_remove_var(env, argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
