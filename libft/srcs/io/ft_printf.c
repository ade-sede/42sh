/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seddaoud <seddaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 15:32:25 by seddaoud          #+#    #+#             */
/*   Updated: 2017/08/30 19:23:52 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdarg.h>
#include <unistd.h>

static void	ft_putcfd(int fd, char c)
{
	write(fd, &c, 1);
}

static void	ft_putsfd(int fd, const char *str)
{
	if (str && *str)
		write(fd, str, ft_strlen(str));
}

static void	ft_putnfd(int fd, int nb)
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

void		ft_printf(char *str, ...)
{
	va_list		ap;
	char		*percent;

	va_start(ap, str);
	while ((percent = ft_strchr(str, '%')))
	{
		if (percent != str)
			write(1, str, (unsigned int)(percent - str));
		if (*++percent == 's')
			ft_putstr(va_arg(ap, const char*));
		else if (*percent == 'd')
			ft_putnbr(va_arg(ap, int));
		else if (*percent == 'c')
			ft_putchar((char)va_arg(ap, int));
		str = percent + 1;
	}
	if (*str)
		ft_putstr(str);
}

void		ft_dprintf(int fd, char *str, ...)
{
	va_list		ap;
	char		*percent;

	va_start(ap, str);
	while ((percent = ft_strchr(str, '%')))
	{
		if (percent != str)
			write(fd, str, (unsigned int)(percent - str));
		if (*++percent == 's')
			ft_putsfd(fd, va_arg(ap, const char*));
		else if (*percent == 'd')
			ft_putnfd(fd, va_arg(ap, int));
		else if (*percent == 'c')
			ft_putcfd(fd, (char)va_arg(ap, int));
		str = percent + 1;
	}
	if (*str)
		ft_putsfd(fd, str);
}
