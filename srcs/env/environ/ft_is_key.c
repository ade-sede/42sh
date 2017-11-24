/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_key(const char *key)
{
	return (ft_str_isdigit(key) || ft_strequ(key, "@") || ft_strequ(key, "*") ||
		ft_strequ(key, "#") || ft_strequ(key, "?") || ft_strequ(key, "-") ||
		ft_strequ(key, "$") || ft_strequ(key, "!"));
}
