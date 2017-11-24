/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vasprintf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:56 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int		ft_vasprintf(char **buffer, const char *format, va_list ap)
{
	int		ret;

	ret = 0;
	ret = buff_loop(format, buffer, ap);
	return (ret);
}
