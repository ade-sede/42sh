/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int		ft_dprintf(int fd, const char *format, ...)
{
	char	*str;
	int		ret;
	va_list ap;

	if (fd < 0)
		return (-1);
	va_start(ap, format);
	ret = ft_vasprintf(&str, format, ap);
	ft_putstr_fd(str, fd);
	free(str);
	va_end(ap);
	return (ret);
}
