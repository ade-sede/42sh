/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:43:09 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/24 10:46:25 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtin.h"

int	builtin_exit(t_env *env, const char **argv)
{
	int		exit_status;
	int		argc;

	argc = ft_arraylen(argv);
	if (argc == 1)
		exit(env->previous_exit);
	if (argc > 2)
		return (return_failure("exit: to many arguments", NULL));
	else if (!(ft_atoi_safe(argv[1], &exit_status)))
		return (return_failure("exit: numeric argument required", NULL));
	else
	{
		conf_term_out();
		exit(exit_status);
	}
	return (EXIT_SUCCESS);
}
