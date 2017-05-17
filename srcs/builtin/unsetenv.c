/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:51:04 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/17 16:34:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>

void	ft_unsetenv(char **argv, t_env **env)
{
	int		i;

	i = 1;
	if (ft_strstrlen(argv) == 1)
	{
		ft_putstr_fd("unsetenv: Too few arguments\n", 2);
		return ;
	}
	while (argv[i])
	{
		ft_delete_var(env, argv[i]);
		i++;
	}
}
