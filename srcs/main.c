/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:38:25 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/16 12:41:14 by ade-sede         ###   ########.fr       */
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
	/* print_environ((const char **)env.environ); */
	/* first = env.path; */
	/* while (first) */
	/* { */
	/* 	ft_printf("%s\n", first->data); */
	/* 	first = first->next; */
	/* } */



	char	*str[] = 	{"/bin/echo", "lol", NULL };
	execve(str[0], str, env.environ);

	return (0);
}
