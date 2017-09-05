/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:43:25 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/14 17:08:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <stdio.h>

int	main(void)
{
	char	**array1;

	array1 = malloc(sizeof(char*) * 10 + 1);
	array1[0] = "lol0";
	array1[1] = "lol1";
	array1[2] = "lol2";
	array1[3] = "lol3";
	array1[4] = "lol4";
	array1[5] = "lol5";
	array1[6] = "lol6";
	array1[7] = "lol7";
	array1[8] = "lol8";
	array1[9] = "lol9";
	array1[10] = NULL;	

	int	i = 0;
	while (array1[i] != NULL)
	{
		printf("%s\n", array1[i]);
		i++;
	}
	i = 0;
	ft_printf("\n");
	array1 = (char**)ft_array_remove(5, 11, (void**)array1);
	i = 0;
	while (array1[i] != NULL)
	{
		printf("%s\n", array1[i]);
		i++;
	}
	return(0);
}
