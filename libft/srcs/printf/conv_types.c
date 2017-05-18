/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 14:59:51 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/13 15:44:20 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_exception(t_opt **opt, char *str)
{
	if (conv_type(opt) == OCT && (*opt)->sharp_flag == 1
			&& (*opt)->dot_flag == 1 && (*opt)->prec == 0)
		(*opt)->exc = 1;
	else
	{
		if (*str == '0')
			(*opt)->sharp_flag = 0;
	}
}

int		conv_type(t_opt **opt)
{
	if ((*opt)->conv_flag == 'c' || (*opt)->conv_flag == 'C')
		return (CHAR);
	if ((*opt)->conv_flag == 's' || (*opt)->conv_flag == 'S')
		return (STR);
	if ((*opt)->conv_flag == 'o' || (*opt)->conv_flag == 'O')
		return (OCT);
	if ((*opt)->conv_flag == 'x' || (*opt)->conv_flag == 'X'
			|| (*opt)->conv_flag == 'p')
		return (HEX);
	if ((*opt)->conv_flag == 'd' || (*opt)->conv_flag == 'i'
			|| (*opt)->conv_flag == 'D')
		return (INT);
	return (0);
}
