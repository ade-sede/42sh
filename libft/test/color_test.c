/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:27:57 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/14 13:37:37 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int	main(void)
{
	ft_printf(CYN"lol\n"RESET);
	ft_putstr(CYN"lol\n"RESET);
	ft_printf(PNK"lol\n"RESET);
	ft_putstr(PNK"lol\n"RESET);
	return (0);
}
