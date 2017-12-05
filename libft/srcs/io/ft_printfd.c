/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seddaoud <seddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 15:32:25 by seddaoud          #+#    #+#             */
/*   Updated: 2017/08/30 19:23:52 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

#include <stdarg.h>
#include <unistd.h>

void	ft_putcfd(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putsfd(int fd, const char *str)
{
	if (str && *str)
		write(fd, str, ft_strlen(str));
}

void	ft_putnfd(int fd, int nb)
{
	unsigned int	index;

	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	index = 1;
	while ((unsigned int)nb / index > 9)
		index *= 10;
	while (index)
	{
		ft_putcfd(fd, (char)((unsigned int)nb / index % 10) + '0');
		index /= 10;
	}
}

void	ft_putunfd(int fd, unsigned int nb)
{
	unsigned int	index;

	index = 1;
	while ((unsigned int)nb / index > 9)
		index *= 10;
	while (index)
	{
		ft_putcfd(fd, (char)((unsigned int)nb / index % 10) + '0');
		index /= 10;
	}
}
