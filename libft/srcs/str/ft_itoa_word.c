/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:06 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "alloc.h"
#include "mem.h"

char	*ft_itoa_word(int n, char nbr[20])
{
	char	*res;
	int		i;

	i = -1;
	ft_bzero(nbr, 20);
	res = ft_itoa_base(n, 10);
	while (res[++i])
		nbr[i] = res[i];
	nbr[i] = '\0';
	free(res);
	return (nbr);
}
