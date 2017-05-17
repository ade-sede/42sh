/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:26:17 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/17 21:36:41 by etieberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	builtin_exit(t_env *env, char **argv)
{
	int		exit_status;
	int		argc;

	argc = ft_arraylen(argv);
	if (argc == 1)
		exit(env->previous_exit);
	if (argc > 2)
		ft_return_err("exit: ", "to many arguments");
	else if (!(ft_atoi_safe(argv[1], &exit_status)))
		ft_return_err("exit: ", "numeric argument required");
	else
		exit(exit_status);
}
