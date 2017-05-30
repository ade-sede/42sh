/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_fcts2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:04:42 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/13 15:15:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_p(t_opt **opt, va_list ap)
{
	(*opt)->sharp_flag = 1;
	(*opt)->len_mod = L;
	return (ft_x(opt, ap));
}

char	*ft_upper_x(t_opt **opt, va_list ap)
{
	return (ft_upstr(ft_x(opt, ap)));
}

char	*ft_o(t_opt **opt, va_list ap)
{
	char		*str;
	uintmax_t	arg;

	if ((*opt)->conv_flag == 'O')
		(*opt)->len_mod = L;
	if ((*opt)->len_mod == 0)
		arg = va_arg(ap, unsigned int);
	if ((*opt)->len_mod == L)
		arg = va_arg(ap, unsigned long int);
	if ((*opt)->len_mod == LL)
		arg = va_arg(ap, unsigned long long int);
	if ((*opt)->len_mod == H)
		arg = (unsigned short)va_arg(ap, unsigned int);
	if ((*opt)->len_mod == HH)
		arg = (unsigned char)va_arg(ap, unsigned int);
	if ((*opt)->len_mod == Z)
		arg = va_arg(ap, size_t);
	if ((*opt)->len_mod == J)
		arg = va_arg(ap, uintmax_t);
	str = ft_unsigned_itoa_base(arg, 8);
	if (arg == 0)
		ft_exception(opt, str);
	add_flags(&str, opt);
	(*opt)->conv_ret = ft_strlen(str);
	return (str);
}

char	*ft_u(t_opt **opt, va_list ap)
{
	char		*str;
	uintmax_t	arg;

	if ((*opt)->conv_flag == 'U')
		(*opt)->len_mod = L;
	if ((*opt)->len_mod == 0)
		arg = va_arg(ap, unsigned int);
	if ((*opt)->len_mod == L)
		arg = va_arg(ap, unsigned long int);
	if ((*opt)->len_mod == LL)
		arg = va_arg(ap, unsigned long long int);
	if ((*opt)->len_mod == H)
		arg = (unsigned short)va_arg(ap, unsigned int);
	if ((*opt)->len_mod == HH)
		arg = (unsigned char)va_arg(ap, unsigned int);
	if ((*opt)->len_mod == Z)
		arg = va_arg(ap, size_t);
	if ((*opt)->len_mod == J)
		arg = va_arg(ap, uintmax_t);
	str = ft_unsigned_itoa_base(arg, 10);
	add_flags(&str, opt);
	(*opt)->conv_ret = (int)ft_strlen(str);
	return (str);
}

char	*ft_b(t_opt **opt, va_list ap)
{
	char		*str;
	uintmax_t	arg;

	if ((*opt)->len_mod == 0)
		arg = va_arg(ap, unsigned int);
	if ((*opt)->len_mod == L)
		arg = va_arg(ap, unsigned long int);
	if ((*opt)->len_mod == LL)
		arg = va_arg(ap, unsigned long long int);
	if ((*opt)->len_mod == H)
		arg = va_arg(ap, unsigned int);
	if ((*opt)->len_mod == HH)
		arg = va_arg(ap, unsigned int);
	str = ft_unsigned_itoa_base(arg, 2);
	add_flags(&str, opt);
	(*opt)->conv_ret = (int)ft_strlen(str);
	return (str);
}
