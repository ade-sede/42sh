/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:26:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/13 15:41:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int	get_nb_digit(uintmax_t value, int base)
{
	int		nb_digit;

	nb_digit = 0;
	while (value > 0)
	{
		value /= base;
		nb_digit++;
	}
	return (nb_digit);
}

char		*ft_unsigned_itoa_base(uintmax_t value, int base)
{
	int		nb_digit;
	char	*str;

	if (value == 0)
		return (ft_strdup("0"));
	nb_digit = get_nb_digit(value, base);
	if (!(str = ft_strnew(nb_digit)))
		return (NULL);
	nb_digit--;
	while (nb_digit >= 0)
	{
		str[nb_digit] = (value % base) + ((value % base > 9) ? 'a' - 10 : '0');
		value /= base;
		nb_digit--;
	}
	return (str);
}
