/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:40:05 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/30 16:11:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	str_prec(char **str, t_opt **opt, char **new_str)
{
	if ((*opt)->prec != 0)
		*new_str = ft_strndup(*str, (*opt)->prec);
	if ((*opt)->prec == 0)
		if ((*opt)->dot_flag == 1)
			*new_str = ft_strdup("\0");
}

void	add_prec(char **str, t_opt **opt)
{
	char	*new_str;
	int		missing_digits;
	char	*padded_str;

	if (*str[0] == '0')
		if ((*opt)->dot_flag == 1 && (*opt)->prec == 0 && (*opt)->exc == 0)
			*str[0] = '\0';
	new_str = NULL;
	missing_digits = (*opt)->prec - (int)ft_strlen(*str);
	if (conv_type(opt) == STR)
		str_prec(str, opt, &new_str);
	else if (conv_type(opt) != STR && missing_digits > 0
			&& conv_type(opt) != CHAR && conv_is_valid((*opt)->conv_flag))
	{
		(*opt)->printf_pad_char = ' ';
		padded_str = pad(missing_digits, '0');
		new_str = ft_strjoin(padded_str, *str);
		free(padded_str);
	}
	if (new_str != NULL)
	{
		free(*str);
		*str = new_str;
	}
}
