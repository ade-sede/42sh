/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:37:00 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/30 16:11:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

static void	is_zero_okay(t_opt **opt, int flag_pos)
{
	if (flag_pos == 0)
	{
		(*opt)->place_holder[flag_pos] = 127;
		(*opt)->printf_pad_char = '0';
	}
	if (flag_pos > 0)
		if ((*opt)->place_holder[flag_pos - 1] != '.'
				&& !ft_isdigit((*opt)->place_holder[flag_pos - 1]))
		{
			(*opt)->place_holder[flag_pos] = 127;
			(*opt)->printf_pad_char = '0';
		}
}

void		get_flags(t_opt **opt)
{
	int		flag_pos;

	flag_pos = ft_strmatch((*opt)->flag_base, (*opt)->place_holder);
	if ((*opt)->place_holder[flag_pos] == '-')
		(*opt)->minus_flag = 1;
	if ((*opt)->place_holder[flag_pos] == '+')
		(*opt)->plus_flag = 1;
	if ((*opt)->place_holder[flag_pos] == '#')
		(*opt)->sharp_flag = 1;
	if ((*opt)->place_holder[flag_pos] == ' ')
		(*opt)->space_flag = 1;
	if ((*opt)->place_holder[flag_pos] == '0')
		is_zero_okay(opt, flag_pos);
	if ((*opt)->place_holder[flag_pos] != '0')
		(*opt)->place_holder[flag_pos] = 127;
}

void		get_fields_info(t_opt **opt, va_list ap)
{
	int		field_len_start;

	field_len_start = ft_strmatch((*opt)->digit_base, (*opt)->place_holder);
	if ((*opt)->place_holder[field_len_start] == '*')
	{
		(*opt)->field_len = va_arg(ap, int);
		(*opt)->place_holder[field_len_start] = 127;
	}
	else
	{
	(*opt)->field_len = ft_abs(ft_atoi((*opt)->place_holder + field_len_start));
	while (ft_isdigit((*opt)->place_holder[field_len_start]))
	{
		(*opt)->place_holder[field_len_start] = 127;
		field_len_start++;
	}
	}
}

void		get_prec(t_opt **opt, va_list ap)
{
	int		prec_pos;
	int		dot;

	dot = 0;
	prec_pos = ft_strichr((*opt)->place_holder, '.');
	if (prec_pos != -1)
		(*opt)->dot_flag = 1;
	if ((*opt)->place_holder[prec_pos + 1] && (*opt)->place_holder[prec_pos + 1] == '*')
		(*opt)->prec = va_arg(ap, int);
	else
	{
	(*opt)->prec = ft_atoi((*opt)->place_holder + prec_pos + 1);
	while (ft_isdigit((*opt)->place_holder[prec_pos])
			|| (*opt)->place_holder[prec_pos] == '.')
	{
		if ((*opt)->place_holder[prec_pos] == '.')
		{
			if (dot > 0)
				get_prec(opt, ap);
			dot++;
		}
		(*opt)->place_holder[prec_pos] = 127;
		prec_pos++;
	}
	if ((*opt)->prec < 0)
		(*opt)->prec = 0;
	}
}

void		get_mode(t_opt **opt)
{
	int		conv_index;

	conv_index = ft_strichr((*opt)->place_holder, (*opt)->conv_flag);
	if (conv_index > 0 && (*opt)->place_holder[conv_index - 2] == 'h')
	{
		(*opt)->len_mod += H;
		if (conv_index > 1 && (*opt)->place_holder[conv_index - 3] == 'h')
			(*opt)->len_mod += H;
	}
	if (conv_index > 0 && (*opt)->place_holder[conv_index - 2] == 'l')
	{
		(*opt)->len_mod += L;
		if (conv_index > 1 && (*opt)->place_holder[conv_index - 3] == 'l')
			(*opt)->len_mod += L;
	}
	if (conv_index > 0 && (*opt)->place_holder[conv_index - 2] == 'j')
		(*opt)->len_mod += J;
	if (conv_index > 0 && (*opt)->place_holder[conv_index - 2] == 'z')
		(*opt)->len_mod += Z;
}
