/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:44:08 by ade-sede          #+#    #+#             */
/*   Updated: 2017/04/04 18:39:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list ap;
	char	*buffer;
	int		printf_ret;

	if (ft_strcmp(format, "%") == 0)
		return (0);
	if (*format == 0)
		return (0);
	printf_ret = 0;
	va_start(ap, format);
	if (!(buffer = malloc(1)))
		return (-1);
	*buffer = 0;
	printf_ret = bufferise(&buffer, format, ap);
	if (ft_strichr(buffer, -10) != -1)
		ft_strnreplace(buffer, -10, 0, printf_ret);
	write(fd, buffer, printf_ret);
	free(buffer);
	va_end(ap);
	return (printf_ret);
}
