/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:35:03 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/31 16:46:54 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static char	*remove_sign(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*unsigned_str;

	size = (int)ft_strlen(str);
	i = 1;
	j = 0;
	unsigned_str = malloc(sizeof(char) * size);
	while (i != size)
	{
		unsigned_str[j] = str[i];
		i++;
		j++;
	}
	unsigned_str[j] = str[i];
	return (unsigned_str);
}

void		add_flags(char **str, t_opt **opt)
{
	char	*unsigned_str;
	int		neg;

	if ((conv_type(opt) == INT || conv_type(opt) == HEX
				|| conv_type(opt)) == OCT && (*opt)->prec > 0)
		(*opt)->printf_pad_char = ' ';
	neg = (*str[0] == '-' && conv_type(opt) == INT) ? 1 : 0;
	if (neg == 1)
	{
		unsigned_str = remove_sign(*str);
		free(*str);
		*str = unsigned_str;
	}
	if ((*opt)->printf_pad_char == ' ')
	{
		add_prec(str, opt);
		add_form(str, opt, neg);
		create_field(str, opt, (int)ft_strlen(*str));
	}
	if ((*opt)->printf_pad_char == '0')
	{
		add_prec(str, opt);
		create_field(str, opt, get_form_size(opt, neg) + (int)ft_strlen(*str));
		add_form(str, opt, neg);
	}
}
