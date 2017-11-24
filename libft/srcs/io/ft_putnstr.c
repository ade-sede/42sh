/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:38 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:52 by ade-sede         ###   ########.fr       */
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

void	ft_putnstr_fd(int fd, char *str, size_t len)
{
	unsigned int strlen;

	strlen = ft_strlen(str);
	if (strlen > len)
		write(fd, str, len);
	else
		write(fd, str, strlen);
}
