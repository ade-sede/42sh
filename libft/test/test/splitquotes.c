/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitquotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 11:26:01 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 12:01:31 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(int ac, char *av[])
{
	char	*str;
	char	**ret;

	if (ac == 2)
		str = av[1];
	else
		str = "This \"is a casual\"	test";

	ret = ft_strsplit_quote((const char*)str, '"', 1);
	while (*ret)
	{
		printf("%s\n", *ret);
		ret++;
	}
	return (0);
}
