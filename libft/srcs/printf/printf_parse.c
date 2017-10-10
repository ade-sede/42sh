/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 18:39:42 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include <stdio.h>

static int	get_prec(const char *format, size_t *format_index, va_list ap)
{
	int	ret;

	(*format_index)++;
	ret = 0;
	if (format[*format_index] == '*')
	{
		(*format_index)++;
		return (va_arg(ap, int));
	}
	else
	{
		while (format[*format_index] >= '0' && format[*format_index] <= '9')
		{
			ret = (ret * 10) + (format[*format_index] - '0');
			(*format_index)++;
		}
	}
	return (ret);
}

static int	get_fieldwidth(const char *format, size_t *format_index, va_list ap)
{
	int	ret;

	ret = 0;
	if (format[*format_index] == '*')
	{
		(*format_index)++;
		return (va_arg(ap, int));
	}
	else
	{
		while (format[*format_index] >= '0' && format[*format_index] <= '9')
		{
			ret = (ret * 10) + (format[*format_index] - '0');
			(*format_index)++;
		}
	}
	return (ret);
}

static int	get_lenmod(const char *format, size_t *format_index, int *ret)
{
	while (format[*format_index] && P_ISLENMOD(format[*format_index]))
	{
		if (format[*format_index++] == 'l')
		{
			if (format[*format_index] == 'l')
				*ret |= _P_LLMOD;
			else
				*ret |= _P_LMOD;
		}
		if (format[*format_index++] == 'h')
		{
			if (format[*format_index] == 'h')
				*ret |= _P_HHMOD;
			else
				*ret |= _P_HMOD;
		}
		if (format[*format_index] == 'j')
			*ret |= _P_JMOD;
		if (format[*format_index] == 'z')
			*ret |= _P_ZMOD;
		if (format[*format_index])
			(*format_index)++;
	}
	return (1);
}

static int	get_opt(const char *format, size_t *format_index, int *ret)
{
	if (format[*format_index] == '#')
		*ret |= _P_SHARP;
	else if (format[*format_index] == '+')
		*ret |= _P_PLUS;
	else if (format[*format_index] == '-')
		*ret |= _P_MINUS;
	else if (format[*format_index] == ' ')
		*ret |= _P_SPACE;
	else if (format[*format_index] == '0')
		*ret |= _P_ZERO;
	(*format_index)++;
	return (1);
}

t_pinfo		printf_parse(const char *format, size_t *format_index, va_list ap)
{
	t_pinfo	pinfo;

	pinfo.p_prec = 0;
	pinfo.p_fieldwidth = 0;
	pinfo.p_lenmod = 0;
	pinfo.p_opt = 0;
	(*format_index)++;
	while (format[*format_index] && P_ISVALID(format[*format_index]))
	{
		if (format[*format_index] == '.')
			pinfo.p_prec = get_prec(format, format_index, ap);
		if (P_ISOPT(format[*format_index]))
			get_opt(format, format_index, &pinfo.p_opt);
		if (ft_isdigit(format[*format_index]) || format[*format_index] == '*')
			pinfo.p_fieldwidth = get_fieldwidth(format, format_index, ap);
		if (P_ISLENMOD(format[*format_index]))
			get_lenmod(format, format_index, &pinfo.p_lenmod);
	}
	pinfo.p_convtype = format[*format_index];
	return (pinfo);
}
