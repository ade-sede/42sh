/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 17:30:10 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/14 17:34:30 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"


int	main(int ac, char *av[])
{
	char		**test;

	test = split_test(av[1], av[2]);
	while (*test != NULL)
	{
		ft_printf("%s\n", *test);
		test++;
	}
	return (0);
}
