/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchange.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 23:25:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/15 12:08:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strchange(void *old, void *new)
{
	free(old);
	return (new);
}

unsigned long int		ft_freeswap(unsigned long int old, unsigned long int new)
{
	free((void*)old);
	return (new);
}
