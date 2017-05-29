/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 12:21:04 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/25 23:16:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

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
}

int	main(void)
{
	print_type_size();
	return (0);
}
