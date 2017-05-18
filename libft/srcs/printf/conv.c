/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 13:50:48 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/16 18:19:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	no_conv(const char *format)
{
	if (*format == 0)
		return (1);
	return (0);
}

void		fill_fcts(char *(**f)(t_opt**, va_list))
{
	f[0] = ft_s;
	f[1] = ft_upper_s;
	f[2] = ft_p;
	f[3] = ft_d;
	f[4] = ft_d;
	f[5] = ft_d;
	f[6] = ft_o;
	f[7] = ft_o;
	f[8] = ft_u;
	f[9] = ft_u;
	f[10] = ft_x;
	f[11] = ft_upper_x;
	f[12] = ft_c;
	f[13] = ft_c;
	f[14] = ft_b;
}

char		*convert(const char *format, va_list ap, t_opt **opt, int *ret)
{
	int		i;
	char	*(*f[15])(t_opt**, va_list);
	char	*str;

	if (no_conv(format) == 1)
		return (ft_chartostr(0));
	i = 0;
	fill_fcts(f);
	while ((*opt)->conv_base[i] && (*opt)->conv_base[i] != (*opt)->conv_flag)
		i++;
	if ((*opt)->conv_base[i] == 0)
	{
		str = ft_chartostr((*opt)->conv_flag);
		add_flags(&str, opt);
		(*opt)->conv_ret = (int)ft_strlen(str);
	}
	else
		str = (f)[i](opt, ap);
	*ret += (*opt)->conv_ret;
	return (str);
}

int			conv_is_valid(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
			c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
			c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == 'b')
		return (1);
	return (0);
}

int			conv_size(const char *format)
{
	int		end_index;

	end_index = 0;
	while (format[end_index] != '\0')
	{
		if (conv_is_valid(format[end_index]))
			break ;
		if (!is_opt(format[end_index]) && !is_len_mod(format[end_index]))
			break ;
		end_index++;
	}
	return (end_index);
}
