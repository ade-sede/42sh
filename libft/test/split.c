/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 17:30:10 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/22 16:29:58 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"


static void	test_split_keep(void)
{
	char	*str;
	char	*split_base = " 	\n\t\v";
	char	**test;

	str = "This is a simple test";
	test = ft_strsplit_keep((const char*)str, (const char*)split_base);
	for (int i = 0; test[i]; i++)
		printf("%s\n", test[i]);
}

int	main(int ac, char *av[])
{
	char		**test;
	char	*str;
	char	*split_base;

	test_split_keep();
/*
**	if (ac == 2)
**		str = av[1];
**	else
**		str = "\"    \"lol";
**	split_base = WHITESPACE;
**	test = ft_strsplit_quotes((const char*)str, (const char*)split_base);
**	while (*test)
**	{
**		ft_printf("%s\n", *test);
**		test++;
**	}
*/
	return (0);
}
