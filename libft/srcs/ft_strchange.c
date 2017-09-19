/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchange.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

void				*ft_strchange(void *old, void *new)
{
	free(old);
	return (new);
}

unsigned long int	ft_freeswap(unsigned long int old, unsigned long int new)
{
	free((void*)old);
	return (new);
}
