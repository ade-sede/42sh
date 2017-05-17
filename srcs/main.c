/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:38:25 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 20:50:15 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "printf.h"

int	main(void)
{
	t_env			env;
	extern const char	**environ;

	env_load_base_env(&env, environ);
	env_print_environ((const char **)env.environ);

	/* size_t index; */

	/* env_getenv((const char**)env.environ, "SHLVL", &index); */
	/* env.environ = (char**)ft_freeswap((t_ulong)env.environ, (t_ulong)env_remove_var(env.environ, env.environ_size, index)); */
	/* env_print_environ((const char **)env.environ); */

	/* t_list		*first; */
	/* first = env.path; */
	/* while (first) */
	/* { */
	/* 	ft_printf("%s\n", first->data); */
	/* 	first = first->next; */
	/* } */
	return (0);
}


