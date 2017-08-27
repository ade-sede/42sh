/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:13:13 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:13:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include <sys/types.h>

intmax_t	ft_abs(intmax_t value)
{
	return ((value >= 0) ? (long)value : (long)-(value));
}
