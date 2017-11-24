/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:18 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_strspush(char **str, char *push)
{
	char			*n_str;
	unsigned int	strlen;
	unsigned		pushlen;

	strlen = ft_strlen(*str);
	pushlen = ft_strlen(push);
	n_str = (strlen / 32 == (strlen + pushlen) / 32
		&& strlen) ? *str : (char*)ft_memalloc(sizeof(char) * (strlen + pushlen
		+ 32 - (strlen + pushlen) % 32 + 1));
	n_str[strlen + pushlen] = '\0';
	while (pushlen--)
		n_str[strlen + pushlen] = push[pushlen];
	if (n_str == *str)
		return ;
	while (strlen--)
		n_str[strlen] = (*str)[strlen];
	free(*str);
	*str = n_str;
}
