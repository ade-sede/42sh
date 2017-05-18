/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:34:28 by ade-sede          #+#    #+#             */
/*   Updated: 2017/02/13 15:28:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	add_form(char **str, t_opt **opt, int neg)
{
	char	*little;
	char	*new_str;

	little = NULL;
	if ((*opt)->sharp_flag > 0 && conv_type(opt) != INT)
	{
		if (conv_type(opt) == HEX)
			little = "0x";
		if (conv_type(opt) == OCT && (*opt)->exc == 0 && **str != '0')
			little = "0";
	}
	else if ((*opt)->plus_flag > 0 && conv_type(opt) == INT && neg == 0)
		little = "+";
	else if ((*opt)->plus_flag == 0 && (*opt)->space_flag > 0
			&& conv_type(opt) == INT && neg == 0)
		little = " ";
	else if (neg == 1)
		little = "-";
	if (little != NULL)
	{
		if (!(new_str = ft_strjoin(little, *str)))
			exit(1);
		free(*str);
		*str = new_str;
	}
}
