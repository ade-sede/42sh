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

#include "printf.h"

#include <stdarg.h>
#include <unistd.h>

void		ft_printf(const char *str, ...)
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
		else if (*percent == 'u')
			ft_putunfd(0, va_arg(ap, unsigned int));
		else if (*percent == 'c')
			ft_putchar((char)va_arg(ap, int));
		str = percent + 1;
	}
	if (*str)
		ft_putstr(str);
}

void		ft_dprintf(int fd, const char *str, ...)
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
		else if (*percent == 'u')
			ft_putunfd(fd, va_arg(ap, unsigned int));
		else if (*percent == 'c')
			ft_putcfd(fd, (char)va_arg(ap, int));
		str = percent + 1;
	}
	if (*str)
		ft_putsfd(fd, str);
}
