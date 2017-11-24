/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:29 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 18:30:09 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int		ft_asprintf(char **buffer, const char *format, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, format);
	ret = ft_vasprintf(buffer, format, ap);
	va_end(ap);
	return (ret);
}
