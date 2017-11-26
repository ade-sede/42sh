/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_prec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int	p_prec(t_pab *s_buf, size_t len, t_pinfo pinfo)
{
	size_t	missing_digits;

	missing_digits = pinfo.p_prec - len;
	if (missing_digits > 0)
	{
		if (s_buf->buf_index + missing_digits > s_buf->buf_size - 1)
			p_realloc_buffer(s_buf);
		ft_memset(s_buf->buf + s_buf->buf_index, '0', missing_digits);
		s_buf->buf_index += missing_digits;
		return (missing_digits);
	}
	return (0);
}
