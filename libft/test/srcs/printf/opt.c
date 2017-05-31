/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:01:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/30 16:11:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_opt	*init_opt(const char *format)
{
	t_opt	*opt;

	if (!(opt = (t_opt*)malloc(sizeof(t_opt))))
		exit(1);
	opt->exc = 0;
	opt->dot_flag = 0;
	opt->conv_index = conv_size(format);
	opt->sharp_flag = 0;
	opt->plus_flag = 0;
	opt->minus_flag = 0;
	opt->space_flag = 0;
	opt->printf_pad_char = ' ';
	opt->field_len = 0;
	opt->prec = 0;
	opt->len_mod = 0;
	opt->conv_base = "sSpdDioOuUxXcCb";
	opt->opt_base = "-+# 0123456789.*";
	opt->flag_base = "-+# 0";
	opt->digit_base = "123456789*";
	opt->len_mod_base = "lhzj";
	if (opt->conv_index != -1)
		opt->place_holder = ft_strsub(format, 0, opt->conv_index + 1);
	opt->conv_flag = 0;
	opt->conv_ret = 0;
	return (opt);
}

t_opt	*get_opt(const char *format, va_list ap)
{
	t_opt	*opt;

	if (!(opt = init_opt(format)))
		exit(1);
	while (ft_strmatch(opt->opt_base, opt->place_holder) != -1)
	{
		if (ft_strmatch(opt->flag_base, opt->place_holder) != -1)
			get_flags(&opt);
		if (ft_strichr(opt->place_holder, '.') != -1)
			get_prec(&opt, ap);
		if (ft_strmatch(opt->digit_base, opt->place_holder) != -1)
			get_fields_info(&opt, ap);
	}
	get_mode(&opt);
	if (opt->minus_flag == 1)
		opt->printf_pad_char = ' ';
	if (opt->conv_index != -1)
		opt->conv_flag = opt->place_holder[ft_strlen(opt->place_holder) - 1];
	return (opt);
}

int		is_opt(char c)
{
	if (c == '+' || c == '-' || c == '#' || c == ' ' || c == '0' ||
			c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
			c == '6' || c == '7' || c == '8' || c == '9' || c == '.' ||
			c == '*')
		return (1);
	return (0);
}

int		is_len_mod(char c)
{
	if (c == 'l' || c == 'h' || c == 'j' || c == 'z')
		return (1);
	return (0);
}
