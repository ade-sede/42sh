/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:50:24 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/17 22:07:00 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int		builtin_setenv(t_env *env, char **argv)
{
	int		k;
	int		i;
	char	*key;
	char	*value;
	int		argc;

	argc = ft_arraylen(argv);
	if (argc = 1)
		ft_putarray(env->environ);
	i = 1;
	while (i < argc)
	{
		if ((k = ft_strchri(argv[i], '=')) > 0)
		{
			argv[i][k] = '\0';
			key = ft_strdup(argv[i]);
			value = ft_strdup(argv[i] + k + 1);
			env_add_to_env(env, key, value);
			free(key);
			free(value);
		}
		else
			return (return_failure("usage: cp key1=value1 key2=value2 ..", NULL));
		i++;
	}
	return (0);
}
