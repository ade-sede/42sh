/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 01:28:00 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/03 00:41:47 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_printf(const char *format, ...)
{
	va_list ap;
	char	*buffer;
	int		printf_ret;

	if (ft_strcmp(format, "%") == 0)
		return (0);
	if (*format == 0)
		return (0);
	printf_ret = 0;
	va_start(ap, format);
	if (!(buffer = malloc(1)))
		return (-1);
	*buffer = 0;
	printf_ret = bufferise(&buffer, format, ap);
	ft_strnreplace(buffer, -10, 0, printf_ret);
	write(1, buffer, printf_ret);
	free(buffer);
	va_end(ap);
	return (printf_ret);
}

int		bufferise(char **buffer, const char *format, va_list ap)
{
	int		i;
	int		ret;
	int		conv_size;

	ret = 0;
	while (ft_strlen(format) != 0)
	{
		if ((i = ft_strichr((char*)format, '%')) != -1)
		{
			if (i != 0)
			{
				early_join(buffer, ft_strsub(format, 0, i), &ret);
			}
			conv_size = start_conv(buffer, &ret, format + i + 1, ap);
		}
		else
		{
			last_join(buffer, (char*)format, &ret);
		}
		format += (i != -1) ? i + conv_size + 1 : (int)ft_strlen(format);
	}
	return (ret);
}

void	last_join(char **buffer, char *format, int *ret)
{
	char	*new_buff;

	if (!(new_buff = ft_strjoin(*buffer, format)))
		exit(1);
	free(*buffer);
	*buffer = new_buff;
	if (*format != 27)
		*ret += (int)ft_strlen(format);
}

void	early_join(char **buffer, char *little, int *ret)
{
	char	*new_buff;

	if (little == NULL)
		exit(1);
	if (!(new_buff = ft_strjoin(*buffer, little)))
		exit(1);
	*ret += ft_strlen(little);
	free(*buffer);
	free(little);
	*buffer = new_buff;
}

int		start_conv(char **buffer, int *ret, const char *format, va_list ap)
{
	t_opt	*opt;
	char	*new_buff;
	char	*conv;
	int		conv_size;

	opt = get_opt(format);
	conv = convert(format, ap, &opt, ret);
	if (!(new_buff = ft_strjoin(*buffer, conv)))
		exit(1);
	conv_size = opt->conv_index + 1;
	free(*buffer);
	free(opt->place_holder);
	free(opt);
	free(conv);
	*buffer = new_buff;
	return (conv_size);
}
