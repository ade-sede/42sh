/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 15:06:55 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/21 14:17:14 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include "mem.h"
#include "alloc.h"
#include "color.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>


static const char	*casual_printf_char_2(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%c";

	int		arg = 0;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}
static const char	*casual_printf_char_1(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%c";

	int		arg = 48;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}
static const char	*color_printf(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = RED"%s"RESET;

	char *arg = "lol";
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*casual_printf_int_5(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%d";

	int		arg = 120;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*padded_printf_str_2(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%-*s";

	char	*arg = "Test str";
	int	padd = 10;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, padd, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, padd, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*padded_printf_str_1(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%*s";

	char	*arg = "Test str";
	int	padd = 10;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, padd, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, padd, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*casual_printf_int_4(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%.10d";

	int		arg = 20;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*casual_printf_int_3(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%-10d";

	int		arg = 0;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*casual_printf_int_2(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%10d";

	int		arg = 0;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*casual_printf_int_1(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%010d";

	int		arg = 15;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"	#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("cmp returned:	%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*casual_printf_str_1(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "%s";
	char 		*arg = "This is a string";
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format, arg);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format, arg);
	printf("Real asprintf output"MAG"#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

static const char	*long_printf(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	char	*format;
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	format = malloc(sizeof(*format) * 7001);
	format[7000] = 0;
	memset(format, 'U', 7000);
	ret = asprintf(&asprintf_buff, format);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format);
	/* printf("Real asprintf output"MAG"#"CYN"%s"MAG"#\n"RESET, asprintf_buff); */
	/* printf("ft_asprintf output"MAG"#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff); */
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	free(format);
	return (__func__);
}

static const char	*casual_printf(short *error)
{
	printf(CYN"\nLaunching test %s\n"RESET, __func__);
	const char	*format = "xxx";
	char		*asprintf_buff;
	char		*ft_asprintf_buff;
	int	ft_ret;
	int	ret;

	ret = asprintf(&asprintf_buff, format);
	ft_ret = ft_asprintf(&ft_asprintf_buff, format);
	printf("Real asprintf output"MAG"#"CYN"%s"MAG"#\n"RESET, asprintf_buff);
	printf("ft_asprintf output"MAG"#"CYN"%s"MAG"#\n"RESET, ft_asprintf_buff);
	if (ret != ft_ret || strcmp(ft_asprintf_buff, asprintf_buff) != 0)
	{
		printf("%d\n", strcmp(ft_asprintf_buff, asprintf_buff));
		printf("Ret is		%d\n", ft_ret);
		printf("Should be	%d\n", ret);
		*error = TRUE;
	}
	free(ft_asprintf_buff);
	free(asprintf_buff);
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 13, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;
	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &casual_printf;
	f[1] = &long_printf;
	f[2] = &casual_printf_str_1;
	f[3] = &casual_printf_int_1;
	f[4] = &casual_printf_int_2;
	f[5] = &casual_printf_int_3;
	f[6] = &casual_printf_int_4;
	f[7] = &padded_printf_str_1;
	f[8] = &padded_printf_str_2;
	f[9] = &casual_printf_int_5;
	f[10] = &color_printf;
	f[11] = &casual_printf_char_1;
	f[12] = &casual_printf_char_2;
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
		printf(MAG"\nReminder of failed tests\n"RESET);
		for (int i = 0; i < nb_error; i++)
			printf("- %s\n", error_list[i]);
	}
	return (0);
}
