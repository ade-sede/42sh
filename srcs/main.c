/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 14:38:25 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/14 22:59:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "printf.h"

int	main(void)
{
	t_env		env;
	extern const char	**environ;

	env.environ = create_environ(environ, &(env.environ_size));
	/* print_environ((const char **)env.environ); */
	ft_printf("%s\n", ft_get_env((const char **)(env.environ), "SHELL", NULL));
	return (0);
}
