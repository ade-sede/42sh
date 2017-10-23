/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seddaoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 08:55:58 by seddaoud          #+#    #+#             */
/*   Updated: 2017/10/23 09:01:03 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

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
