/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 18:40:29 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 19:10:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"

static int	p_itoa_base(intmax_t value, int base, t_pab *s_buf)
{
	int		nb_digit;
	size_t	len;

	nb_digit = itoa_base_len(value, base);
	len = (size_t)nb_digit;
	if (!value)
		len = 1;
	if (s_buf->buf_index + len > s_buf->buf_size - 1)
		p_realloc_buffer(s_buf);
	if (value == 0)
	{
		s_buf->buf[s_buf->buf_index++] = '0';
		return (1);
	}
	value *= (value > 0) ? -1 : 1;
	while (nb_digit-- > 0)
	{
		(s_buf->buf + s_buf->buf_index - 1)[nb_digit + 1] = \
	(-(value % base) + ((-(value % base) > 9) ? 'a' - 10 : '0'));
		value /= base;
	}
	s_buf->buf_index += len;
	return ((int)len);
}

static int	zero_course(t_pab *s_buf, long long arg, int base, t_pinfo pinfo)
{
	size_t	len;
	int		ret;

	ret = 0;
	len = (size_t)itoa_base_len(arg, base);
	if (pinfo.p_prec)
		ret += p_prec(s_buf, len, pinfo);
	if (P_MINUS(pinfo.p_opt))
	{
		ret += p_itoa_base(arg, base, s_buf);
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
	}
	else
	{
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
		ret += p_itoa_base(arg, 10, s_buf);
	}
	return (ret);
}

static int	space_course(t_pab *s_buf, long long arg, int base, t_pinfo pinfo)
{
	int		ret;
	size_t	len;

	ret = 0;
	len = (size_t)itoa_base_len(arg, base);
	if (pinfo.p_prec)
		ret += p_prec(s_buf, len, pinfo);
	if (P_MINUS(pinfo.p_opt))
	{
		ret += p_itoa_base(arg, 10, s_buf);
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
	}
	else
	{
		if (pinfo.p_fieldwidth)
			ret += p_padd(s_buf, len, pinfo);
		ret += p_itoa_base(arg, 10, s_buf);
	}
	return (ret);
}

int			numeric_conv(t_pab *s_buf, long long arg, int base, t_pinfo pinfo)
{
	int	ret;

	ret = 0;
	if (P_ZERO(pinfo.p_opt))
		ret = zero_course(s_buf, arg, base, pinfo);
	else
		ret = space_course(s_buf, arg, base, pinfo);
	return (ret);
}
