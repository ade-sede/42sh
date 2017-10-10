/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:31 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 19:10:40 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include <stdio.h>

int		p_dconv(t_pinfo pinfo, t_pab *s_buf, va_list ap)
{
	int			ret;
	long long	arg;

	arg = 0;
	if (pinfo.p_lenmod == 0)
		arg = (int)va_arg(ap, long long);
	else if (P_LLMOD(pinfo.p_lenmod))
		arg = va_arg(ap, long long);
	ret = numeric_conv(s_buf, arg, 10, pinfo);
	return (ret);
}
