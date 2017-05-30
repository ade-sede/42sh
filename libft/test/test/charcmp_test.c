/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charcmp_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 14:11:59 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/17 10:53:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(int ac, char *av[])
{
	int	ret;
	/* char	*str = "Thi\s is a test"; */
	char	*str = ft_strdup("\a");
	int i = 0;
	
	ft_putchar(str[i]);	
	ft_putchar('\n');
	ret =	charcmp((const char*)str , i, "a");
	printf("%d\n", ret);
	return (0);
}
