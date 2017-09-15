/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_failure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:38 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:42:09 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

int	return_failure(const char *str, const char *error_msg)
{
	if (str)
		ft_putstr_fd(str, 2);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}
