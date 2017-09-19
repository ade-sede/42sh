/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:54 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:02 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "str.h"

int		ft_strrequ(const char *s1, const char *s2)
{
	if (ft_strrcmp(s1, s2) != 0)
		return (0);
	return (1);
}
