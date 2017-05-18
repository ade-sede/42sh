/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:54:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/04/27 10:28:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	char	**str;
	char	**test;

	test = malloc(sizeof(char*) * 4);
	str = malloc(sizeof(char*) * 4);

	printf("Str add = %p\n", str);
	printf("Test add = %p\n", test);
	printf("\n");

	str[0] = "lol0";
	str[1] = "lol1";
	str[2] = "lol2";
	str[3] = "lol3";

	for(int i = 0; i <= 3; i++)
		printf("1 ---> %s @ %p\n", str[i], str[i]);
	printf("\n");

	test = (char**)ft_addcpy((void**)test, (const void **)str, 4);

	printf("\n");
	printf("Test add = %p\n", test);

	for(int j = 0; j <= 3; j++)
		printf("2 ---> %s @ %p\n", test[j], test[j]);
	return (0);
}
