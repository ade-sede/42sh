/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_padd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int	p_padd(t_pab *s_buf, size_t len, t_pinfo pinfo)
{
	int		missing_fields;
	char	padding_char;

	missing_fields = pinfo.p_fieldwidth - len;
	if (missing_fields > 0)
	{
		padding_char = P_ZERO(pinfo.p_opt) ? '0' : ' ';
		if (s_buf->buf_index + missing_fields > s_buf->buf_size - 1)
			p_realloc_buffer(s_buf);
		ft_memset(s_buf->buf + s_buf->buf_index, padding_char, missing_fields);
		s_buf->buf_index += missing_fields;
		return (missing_fields);
	}
	return (0);
}
