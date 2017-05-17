/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:38:25 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 14:59:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "printf.h"

int	main(void)
{
	t_env			env;
	extern const char	**environ;
	/* t_list		*first; */

	load_base_env(&env, environ);
	print_environ((const char **)env.environ);

	/* size_t index; */

	/* ft_get_env((const char**)env.environ, "SHLVL", &index); */
	/* env.environ = (char**)ft_freeswap((t_ulong)env.environ, (t_ulong)remove_var(env.environ, env.environ_size, index)); */
	/* print_environ((const char **)env.environ); */

	/* first = env.path; */
	/* while (first) */
	/* { */
	/* 	ft_printf("%s\n", first->data); */
	/* 	first = first->next; */
	/* } */
	return (0);
}


