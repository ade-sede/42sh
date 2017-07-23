/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_failure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:55:17 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/23 15:18:43 by ade-sede         ###   ########.fr       */
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
