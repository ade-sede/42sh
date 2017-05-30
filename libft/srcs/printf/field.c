/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:35:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/30 16:11:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	create_field(char **str, t_opt **opt, int form_size)
{
	int		pad_size;
	char	*new_str;
	char	*padded_str;

	if ((*opt)->field_len > 0)
	{
		pad_size = ((*opt)->field_len) - form_size;
		if (pad_size > 0)
		{
			padded_str = pad(pad_size, (*opt)->printf_pad_char);
			if ((*opt)->minus_flag == 1)
				new_str = ft_strjoin(*str, padded_str);
			else
				new_str = ft_strjoin(padded_str, *str);
			free(padded_str);
			free(*str);
			*str = new_str;
		}
	}
}

char	*pad(int pad_size, char c)
{
	char	*padded_str;
	int		i;

	i = 0;
	padded_str = malloc(sizeof(char) * pad_size + 1);
	if (!padded_str)
		exit(1);
	while (i != pad_size)
	{
		padded_str[i] = c;
		i++;
	}
	padded_str[i] = 0;
	return (padded_str);
}

int		get_form_size(t_opt **opt, int neg)
{
	int		form_size;

	form_size = 0;
	if (neg == 1)
		form_size += 1;
	if ((*opt)->sharp_flag > 0)
	{
		if (conv_type(opt) == HEX)
			form_size += 2;
		if (conv_type(opt) == OCT)
			form_size += 1;
	}
	if ((*opt)->space_flag == 1 && neg == 0 && (*opt)->plus_flag == 0)
		form_size += 1;
	if ((*opt)->plus_flag == 1 && neg == 0)
		form_size += 1;
	return (form_size);
}
