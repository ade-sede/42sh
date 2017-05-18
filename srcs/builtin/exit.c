/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:26:17 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/18 15:03:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "env.h"

void	ft_exit(char **argv, int *previous_exit)
{
	int		exit_status;
	int		save_previous_exit;

	if (ft_strstrlen(argv) == 1)
	{
		save_previous_exit = *previous_exit;
		*previous_exit = 0;
		exit(save_previous_exit);
	}
	if (ft_strstrlen(argv) > 2)
		ft_return_err("exit: ", "to many arguments");
	else if (!(ft_atoi_safe(argv[1], &exit_status)))
		ft_return_err("exit: ", "numeric argument required");
	else
		exit(exit_status);
}
