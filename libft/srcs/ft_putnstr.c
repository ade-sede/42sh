/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/08/27 06:58:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr(char *str, size_t len)
{
	unsigned int strlen;

	strlen = ft_strlen(str);
	if (strlen > len)
		write(1, str, len);
	else
		write(1, str, strlen);
}
