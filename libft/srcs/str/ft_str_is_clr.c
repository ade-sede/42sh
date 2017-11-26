/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_clr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:06 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_clr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int		ft_str_is_clear_n(char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && n)
	{
		if (!ft_is_space(str[i]))
			return (FALSE);
		--n;
		++i;
	}
	return (TRUE);
}
