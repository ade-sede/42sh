/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:14 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_strpush(char **str, char c)
{
	char			*n_str;
	unsigned int	len;

	n_str =
		((len = ft_strlen(*str)) % 32) ?
		*str : (char*)ft_memalloc(sizeof(char) * (len + 32 + 1));
	n_str[len] = c;
	n_str[len + 1] = '\0';
	if (n_str == *str)
		return ;
	while (len--)
		n_str[len] = (*str)[len];
	free(*str);
	*str = n_str;
}
