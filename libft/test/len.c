/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:57:01 by ade-sede          #+#    #+#             */
/*   Updated: 2017/04/28 17:01:15 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

int	main()
{
	char	*str[] = { "lol", "lul", "lil", 0, "lol"};
	ft_printf("%zu\n", ft_arraylen((const char**)str));
	return (0);
}
