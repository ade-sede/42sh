/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:39 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_digit_count(int nb)
{
	int		nb_digit;

	nb_digit = 1;
	while (nb > 10)
	{
		nb_digit++;
		nb /= 10;
	}
	return (nb_digit);
}
