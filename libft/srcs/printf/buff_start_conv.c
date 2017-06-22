/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_start_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:30 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 19:21:50 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include <stdio.h>

static	t_pconv	g_pconv[] =
{
	{'d', &p_dconv},
	{'s', &p_sconv},
	{'c', &p_cconv},
	{0, NULL}
};

int		p_isconv(char c)
{
	return (ft_strichr("dspcuoxbDSiOXU", c) == -1 ? 0 : 1);
}

int		p_realloc_buffer(t_pab *s_buf)
{
	s_buf->buf_size += P_BUFF_SIZE;
	s_buf->buf = ft_realloc(s_buf->buf_index, s_buf->buf, s_buf->buf_size);
	return (s_buf->buf_size);
}

int		buff_start_conv(const char *format, size_t *format_index, \
		t_pab *s_buf, va_list ap)
{
	int		ret;
	t_pinfo pinfo;
	int		i;

	i = 0;
	ret = 0;
	pinfo = printf_parse(format, format_index, ap);
	if (!p_isconv(pinfo.p_convtype))
		return (0);
	while (g_pconv[i].key && g_pconv[i].key != pinfo.p_convtype)
		i++;
	ret = g_pconv[i].f(pinfo, s_buf, ap);
	return (ret);
}
