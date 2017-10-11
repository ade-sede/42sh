/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 18:36:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include <stdio.h>

static int		pbuff_str(t_pab *s_buf, size_t len, char *arg)
{
	if (s_buf->buf_index + len > s_buf->buf_size - 1)
	{
		s_buf->buf_size += P_BUFF_SIZE;
		s_buf->buf = ft_realloc(s_buf->buf_index, s_buf->buf, s_buf->buf_size);
	}
	ft_memcpy(s_buf->buf + s_buf->buf_index, arg, len);
	s_buf->buf_index += len;
	return (len);
}

int				p_sconv(t_pinfo pinfo, t_pab *s_buf, va_list ap)
{
	int		ret;
	size_t	len;
	char	*arg;

	ret = 0;
	arg = va_arg(ap, char*);
	len = ft_strlen(arg);
	if (P_MINUS(pinfo.p_opt))
	{
		ret += pbuff_str(s_buf, len, arg);
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
	}
	else
	{
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
		ret += pbuff_str(s_buf, len, arg);
	}
	return (ret);
}
