/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 13:07:10 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 13:10:05 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include <stdio.h>

int		p_uconv(t_pinfo pinfo, t_pab *s_buf, va_list ap)
{
	int				ret;
	unsigned long	arg;

	arg = 0;
	if (pinfo.p_lenmod == 0)
		arg = va_arg(ap, unsigned int);
	else if (P_LLMOD(pinfo.p_lenmod))
		arg = va_arg(ap, unsigned long);
	else if (P_ZMOD(pinfo.p_lenmod))
		arg = (unsigned char)va_arg(ap, unsigned int);
	ret = numeric_conv(s_buf, arg, 10, pinfo);
	return (ret);
}
