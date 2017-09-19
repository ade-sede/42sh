/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:53 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

int	ft_strequ(char const *s1, char const *s2)
{
	if (ft_strcmp(s1, s2) != 0)
		return (0);
	return (1);
}
