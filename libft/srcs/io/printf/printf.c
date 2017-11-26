/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

/*
**	Plan :
**	-Parse the whole format string in 1 go, and retrieve arguments on theway.
*/

int		ft_printf(const char *format, ...)
{
	char	*str;
	int		ret;
	va_list ap;

	va_start(ap, format);
	ret = ft_vasprintf(&str, format, ap);
	ft_putstr(str);
	free(str);
	va_end(ap);
	return (ret);
}
