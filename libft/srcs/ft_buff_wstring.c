/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff_wstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 00:34:02 by ade-sede          #+#    #+#             */
/*   Updated: 2017/01/27 00:49:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_buff_wstring(wchar_t *str)
{
	char	*new_str;
	char	*old_str;
	char	*tmp_wchar;

	new_str = malloc(1);
	if (!new_str)
		exit(1);
	new_str[0] = 0;
	while (*str != 0)
	{
		tmp_wchar = ft_buff_wchar(*str);
		old_str = new_str;
		new_str = ft_strjoin(new_str, tmp_wchar);
		str++;
		free(old_str);
		free(tmp_wchar);
	}
	return (new_str);
}
