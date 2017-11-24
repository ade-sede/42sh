/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:30 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 18:33:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "color.h"
#include "libft.h"
#include <stdio.h>

int		buff_loop(const char *format, char **buffer, va_list ap)
{
	size_t	format_index;
	int		ret;
	t_pab	s_buf;

	ret = 0;
	format_index = 0;
	s_buf.buf_size = P_BUFF_SIZE;
	s_buf.buf_index = 0;
	s_buf.buf = (char*)palloc(sizeof(*(s_buf.buf)) * P_BUFF_SIZE);
	while (format[format_index])
	{
		if (format[format_index] == '%')
			ret += buff_start_conv(format, &format_index, &s_buf, ap);
		else
		{
			pbuff_char(&s_buf, 1, format[format_index]);
			ret++;
		}
		format_index++;
	}
	s_buf.buf[s_buf.buf_index] = 0;
	*buffer = s_buf.buf;
	return (ret);
}
