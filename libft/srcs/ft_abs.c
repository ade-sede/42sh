/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:35 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include <sys/types.h>

intmax_t	ft_abs(intmax_t value)
{
	return ((value >= 0) ? (long)value : (long)-(value));
}
