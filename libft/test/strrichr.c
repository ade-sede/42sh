/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrichr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 12:33:01 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/26 12:34:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "libft.h"
#include "printf.h"
#include <string.h>
#include "str.h"

static const char	*big_strrichr(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*str = "Hwqe iqje wqje oqwje oiwqje oiwqje oqwje oqjwe oqiwe ere comes a 0. Here it is";
	size_t	ret;

	ret = ft_strrichr(str, '0');
	if (str + ret !=strrchr(str, '0'))
		*error = TRUE;
	printf("%c\n", str[ret]);
	if (str[ret] != '0')
		*error = TRUE;
	return (__func__);
}

static const char	*null_strrichr(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*str = "Here comes a . Here it is";
	size_t	ret;

	ret = ft_strrichr(str, '0');
	if (ret != -1)
		*error = TRUE;
	return (__func__);
}

static const char	*casual_strrichr(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*str = "Here comes a 0. Here it is";
	size_t	ret;

	ret = ft_strrichr(str, '0');
	if (str + ret !=strrchr(str, '0'))
		*error = TRUE;
	printf("%c\n", str[ret]);
	if (str[ret] != '0')
		*error = TRUE;
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 3, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;

	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &casual_strrichr;
	f[1] = &null_strrichr;
	f[2] = &big_strrichr;
	while (index < nb_func)
	{
		error = FALSE;
		func_ret = f[index](&error);
		if (error)
		{
			printf(RED"FAIL @ %s\n"RESET, func_ret);
			error_list[nb_error] = func_ret;
			nb_error++;
		}
		else
			printf(GRN"SUCCESS @ %s\n"RESET, func_ret);
		index++;
	}
	if (nb_error)
	{
		printf(MAG"Reminder of failed tests\n"RESET);
		for (int i = 0; i < nb_error; i++)
			printf("- %s\n", error_list[i]);
	}
	return (0);
}
