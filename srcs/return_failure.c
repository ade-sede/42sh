/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_failure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:55:17 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/26 13:55:18 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

int	return_failure(const char *str, const char *error_msg)
{
	if (str)
		ft_putstr(str);
	if (error_msg)
		ft_putstr(error_msg);
	ft_putchar('\n');
	return (EXIT_FAILURE);
}
