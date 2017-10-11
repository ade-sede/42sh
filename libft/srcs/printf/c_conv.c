/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:31 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 19:10:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int			pbuff_char(t_pab *s_buf, size_t len, char c)
{
	if (c)
	{
		if (s_buf->buf_index + len > s_buf->buf_size - 1)
			p_realloc_buffer(s_buf);
		s_buf->buf[s_buf->buf_index++] = c;
		return (1);
	}
	return (0);
}

int			p_cconv(t_pinfo pinfo, t_pab *s_buf, va_list ap)
{
	int		ret;
	size_t	len;
	char	arg;

	ret = 0;
	arg = va_arg(ap, int);
	if (arg == 0)
		ret = 1;
	else
		len = 1;
	if (P_MINUS(pinfo.p_opt))
	{
		ret += pbuff_char(s_buf, len, arg);
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
	}
	else
	{
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
		ret += pbuff_char(s_buf, len, arg);
	}
	return (ret);
}
