/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 02:20:04 by ade-sede          #+#    #+#             */
/*   Updated: 2017/01/30 02:25:08 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ishex(int c)
{
	if ((c >= 'A' && c <= 'F') || ft_isdigit(c) || (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}