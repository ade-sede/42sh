/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 12:21:04 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/20 13:52:48 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <stdio.h>
#include <string.h>
# define PRINTF_SIZEOF(type) printf("sizeof(" #type ") = %zd.\n", sizeof(type))

static void print_type_size(void)
{
	PRINTF_SIZEOF(char);
	PRINTF_SIZEOF(short int);
	PRINTF_SIZEOF(int);
	PRINTF_SIZEOF(long int);
	PRINTF_SIZEOF(long);
	PRINTF_SIZEOF(long long int);
	PRINTF_SIZEOF(long long);
	PRINTF_SIZEOF(t_ulong);
	PRINTF_SIZEOF(intmax_t);
	PRINTF_SIZEOF(uintmax_t);
	PRINTF_SIZEOF(unsigned int);
}

int	buf[2] = {1, 2};
static void	binary_test()
{
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199409L
static void	linker_test()
{
}
#endif

static void	printf_sandbox()
{
}

static void	printf_parse_test()
{
	char	*lol;

	lol = NULL;
	printf(CYN"FIRST TEST\n"RESET);
	ft_asprintf(&lol, "%123.321c\n");
	if (lol)
		free(lol);
	printf(CYN"SECOND TEST\n"RESET);
	lol = NULL;
	ft_asprintf(&lol, "%*c\n", 10);
	if (lol)
		free(lol);
	printf(CYN"THIRD TEST\n"RESET);
	lol = NULL;
	ft_asprintf(&lol, "%.*c\n", 10);
	if (lol)
		free(lol);
}

int	main(void)
{
	/* print_type_size(); */
	/* binary_test(); */
	/* linker_test(); */
	/* printf_sandbox(); */
	printf_parse_test();
	return (0);
}
