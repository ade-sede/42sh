/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:55:45 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/13 15:33:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_s(t_opt **opt, va_list ap)
{
	char	*str;
	char	*arg;

	str = NULL;
	if ((*opt)->len_mod == 0)
	{
		arg = va_arg(ap, char *);
		str = (arg == NULL) ? ft_strdup("(null)") : ft_strdup(arg);
	}
	if ((*opt)->len_mod == L)
		str = ft_upper_s(opt, ap);
	add_flags(&str, opt);
	(*opt)->conv_ret = (int)ft_strlen(str);
	return (str);
}

char	*ft_upper_s(t_opt **opt, va_list ap)
{
	char	*str;
	wchar_t	*arg;

	arg = va_arg(ap, wchar_t*);
	if (arg == NULL)
		str = ft_strdup("(null)");
	else
		str = ft_buff_wstring(arg);
	add_flags(&str, opt);
	(*opt)->conv_ret = (int)ft_strlen(str);
	return (str);
}

char	*ft_d(t_opt **opt, va_list ap)
{
	char		*str;
	intmax_t	arg;

	if ((*opt)->conv_flag == 'D')
		(*opt)->len_mod = L;
	if ((*opt)->len_mod == 0)
		arg = va_arg(ap, int);
	if ((*opt)->len_mod == H)
		arg = (short)va_arg(ap, int);
	if ((*opt)->len_mod == HH)
		arg = (char)va_arg(ap, int);
	if ((*opt)->len_mod == L)
		arg = va_arg(ap, long int);
	if ((*opt)->len_mod == LL)
		arg = va_arg(ap, long long int);
	if ((*opt)->len_mod == J)
		arg = va_arg(ap, intmax_t);
	if ((*opt)->len_mod == Z)
		arg = va_arg(ap, unsigned long int);
	str = ft_itoa_base(arg, 10);
	add_flags(&str, opt);
	(*opt)->conv_ret = (int)ft_strlen(str);
	return (str);
}

char	*ft_c(t_opt **opt, va_list ap)
{
	wchar_t arg;
	char	*str;

	arg = 32;
	if ((*opt)->conv_flag == 'C')
		(*opt)->len_mod = L;
	if ((*opt)->len_mod == 0)
	{
		arg = (wchar_t)va_arg(ap, int);
		if (arg == 0)
			str = ft_buff_wchar(-10);
		else
			str = ft_chartostr(arg);
	}
	if ((*opt)->len_mod == L)
	{
		arg = va_arg(ap, wchar_t);
		if (arg == 0)
			str = ft_buff_wchar(-10);
		else
			str = ft_buff_wchar(arg);
	}
	add_flags(&str, opt);
	(*opt)->conv_ret = (int)ft_strlen(str);
	return (str);
}

char	*ft_x(t_opt **opt, va_list ap)
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
		arg = (unsigned short)va_arg(ap, unsigned int);
	if ((*opt)->len_mod == HH)
		arg = (unsigned char)va_arg(ap, unsigned int);
	if ((*opt)->len_mod == Z)
		arg = va_arg(ap, size_t);
	if ((*opt)->len_mod == J)
		arg = va_arg(ap, uintmax_t);
	str = ft_unsigned_itoa_base(arg, 16);
	if (arg == 0 && (*opt)->conv_flag != 'p')
		(*opt)->sharp_flag = 0;
	add_flags(&str, opt);
	(*opt)->conv_ret = (int)ft_strlen(str);
	return (str);
}
