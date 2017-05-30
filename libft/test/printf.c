/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 01:30:15 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/30 15:06:03 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <assert.h>
#include <stdio.h>////////////////////////////////////////////////////////////
#include <locale.h>///////////////////////////////////////////////////////////
#include <stdlib.h>///////////////////////////////////////////////////////////
#include <limits.h>

int		test_s(void)
{
	printf(MAG"||---------------------- NOW TESTING WITH CASUAL STRINGS AND WIDE STRINGS ---------------||\n"RESET);

	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;
	int		ret3 = 0;
	int		ret4 = 0;
	int		ret5 = 0;
	int		ret6 = 0;
	int		ret7 = 0;
	int		ret8 = 0;
	int		ret9 = 0;
	int		ret10 = 0;
	int		ret11 = 0;
	int		ret12 = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*s_test1 = ft_strdup("Lolilol");
	printf("Testing simple conversion with string \"%s\" : \n", s_test1);
	ret1 = ft_printf("%s%s\n","			", s_test1);
	ret2 = printf("%s%s\n", "			",s_test1);
	if (ret1 != ret2)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret1, ret2);
		test_ret++;
	}
	free(s_test1);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	setlocale(LC_ALL, "");
	wchar_t	s_test2[3];
	s_test2[0] = 0x1234;
	s_test2[1] = 0x1234;
	s_test2[2] = 0;
	printf("Testing simple conversion with wide string \"%S\" : \n", s_test2);
	if ((ret3 = ft_printf("%s%S\n","			",s_test2)) != (ret4 = printf("%s%ls\n","			",s_test2)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret3, ret4);
		test_ret++;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*s_test3 = NULL;
	printf("Conv with %%s and %s pointer : \n", s_test3);
	ret5 = ft_printf("%s%s\n","			", s_test3);
	ret6 = printf("%s%s\n","			", s_test3);
	if (ret5 != ret6)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret5, ret6);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*s_test4 = NULL;
	printf("Conv with %%ls and %s pointer : \n", s_test4);
	ret7 = ft_printf("%s%ls\n","			", s_test4);
	ret8 = printf("%s%ls\n","			", s_test4);
	if (ret7 != ret8)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret7, ret8);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*s_test5 = "Only the word Only should appear";
	printf("Conv with %s and prec 4 pointer : \n", s_test5);
	ret9 = ft_printf("%s%.4s\n","			", s_test5);
	ret10 = printf("%s%.4s\n","			", s_test5);
	if (ret9 != ret10)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret9, ret10);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*s_test6 = "Only the word Only should appear";
	printf("Conv with %s and prec 4 pointer : \n", s_test6);
	ret11 = ft_printf("%s%.4s\n","			", s_test6);
	ret12 = printf("%s%.4s\n","			", s_test6);
	if (ret9 != ret10)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret9, ret10);
		test_ret++;
	}

	return (test_ret);
}

int		test_d(void)
{
	printf(MAG"||---------------------- NOW TESTING WITH CASUAL INTS ------------------||\n"RESET);

	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;
	int		ret3 = 0;
	int		ret4 = 0;
	int		ret5 = 0;
	int		ret6 = 0;
	int		ret7 = 0;
	int		ret8 = 0;
	int		ret9 = 0;
	int		ret10 = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		i_test1 = 0;
	printf("Testing simple conversion with int %d : \n", i_test1);
	if ((ret1 = ft_printf("%s%d\n","			",i_test1)) != (ret2 = printf("%s%d\n","			",i_test1)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret1, ret2);
		test_ret++;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		i_test2 = INT_MAX;
	printf("Testing simple conversion with int %d : \n", i_test2);
	if ((ret3 = ft_printf("%s%d\n","			",i_test2)) != (ret4 = printf("%s%d\n","			",i_test2)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret3, ret4);
		test_ret++;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		i_test3 = INT_MIN;
	printf("Testing simple conversion with int %d : \n", i_test3);
	if ((ret5 = ft_printf("%s%d\n","			",i_test3)) != (ret6 = printf("%s%d\n","			",i_test3)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret5, ret6);
		test_ret++;
	}	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	long	i_test4 = 42147483648;
	printf("Testing simple conversion with long %ld and modifier l : \n", i_test4);
	if ((ret7 = ft_printf("%s%ld\n","			",i_test4)) != (ret8 = printf("%s%ld\n","			",i_test4)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret7, ret8);
		test_ret++;
	}	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	int		i_test5 = 42;
	printf("Testing with unsigned int and '+' flag %d : \n", i_test5);
	if ((ret9 = ft_printf("%s%+ d\n","			", i_test5)) != (ret10 = printf("%s%+ d\n","			", i_test5)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret9, ret10);
		test_ret++;
	}



	return (test_ret);
}

int		test_o(void)
{
	printf(MAG"||---------------------- NOW TESTING OCTAL INTEGERS ------------------||\n"RESET);

	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;
	int		ret3 = 0;
	int		ret4 = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		o_test1 = 52;
	printf("Testing simple conversion with octal int %d : \n", o_test1);
	if ((ret1 = ft_printf("%s%o\n","			",o_test1)) != (ret2 = printf("%s%o\n","			",o_test1)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret1, ret2);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		o_test2 = 48;
	printf("Testing simple conversion with octal int %d : \n", o_test2);
	if ((ret3 = ft_printf("%s%O\n","			",o_test2)) != (ret4 = printf("%s%o\n","			",o_test2)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret3, ret4);
		test_ret++;
	}

	return (test_ret);
}

int		test_u(void)
{
	printf(MAG"||---------------------- NOW TESTING UNSIGNED INT ------------------||\n"RESET);
	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;
	int		ret3 = 0;
	int		ret4 = 0;
	int		ret5 = 0;
	int		ret6 = 0;

	///////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned int		u_test1 = 42;
	printf("Testing simple conversion with unsigned int %d : \n", u_test1);
	if ((ret1 = ft_printf("%s%u\n","			", u_test1)) != (ret2 = printf("%s%u\n","			", u_test1)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret1, ret2);
		test_ret++;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned int		u_test2 = -42;
	printf("Testing simple conversion with unsigned int %d : \n", u_test2);
	if ((ret3 = ft_printf("%s%u\n","			", u_test2)) != (ret4 = printf("%s%u\n","			", u_test2)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret3, ret4);
		test_ret++;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned int		u_test3 = 42;
	printf("Testing with unsigned int and '+' flag %d : \n", u_test3);
	if ((ret5 = ft_printf("%s%+u\n","			", u_test3)) != (ret6 = printf("%s%+u\n","			", u_test3)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret5, ret6);
		test_ret++;
	}

	return (test_ret);
}


int		test_x(void)
{
	printf(MAG"||---------------------- NOW TESTING HEX INTEGERS (INCLUDING MEM ADDR)------------------||\n"RESET);

	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;
	int		ret3 = 0;
	int		ret4 = 0;
	int		ret5 = 0;
	int		ret6 = 0;
	int		ret7 = 0;
	int		ret8 = 0;
	int		ret9 = 0;
	int		ret10 = 0;
	int		ret11 = 0;
	int		ret12 = 0;
	int		ret13 = 0;
	int		ret14 = 0;
	int		ret15 = 0;
	int		ret16 = 0;
	int		ret17 = 0;
	int		ret18 = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		x_test1 = 127;
	printf("Testing simple conversion with hex int %d in lower case : \n", x_test1);
	if ((ret1 = ft_printf("%s%x\n","			",x_test1)) != (ret2 = printf("%s%x\n","			",x_test1)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret1, ret2);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		x_test2 = 127;
	printf("Testing simple conversion with hex int %d in upper case: \n", x_test2);
	if ((ret3 = ft_printf("%s%X\n","			",x_test2)) != (ret4 = printf("%s%X\n","			",x_test2)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret3, ret4);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		x_test3 = INT_MAX;
	printf("Testing simple conversion with hex int %d in lower case : \n", x_test3);
	if ((ret5 = ft_printf("%s%x\n","			",x_test3)) != (ret6 = printf("%s%x\n","			",x_test3)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret5, ret6);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		x_test4 = INT_MAX;
	printf("Testing simple conversion with hex int %d in upper case: \n", x_test4);
	if ((ret7 = ft_printf("%s%X\n","			",x_test4)) != (ret8 = printf("%s%X\n","			",x_test4)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret7, ret8);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	long long	x_test5 = 467777777777;
	printf("Testing conversion with hex int %d in lower case and lenght modifier ll : \n", x_test5);
	if ((ret9 = ft_printf("%s%llx\n","			",x_test5)) != (ret10 = printf("%s%llx\n","			",x_test5)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret9, ret10);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	long long	x_test6 = 0;
	printf("Testing conversion with hex int 0 and # flag : \n", x_test6);
	if ((ret17 = ft_printf("%s%ll#x\n","			",x_test6)) != (ret18 = printf("%s%ll#x\n","			",x_test6)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret17, ret18);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*p_test1 = ft_strdup("test");
	printf("Printing addr : %p : (REAL PRINTF FIRST, then mine) \n", p_test1);
	if ((ret12 = printf("%s%p\n","			",p_test1)) != (ret11 = ft_printf("%s%p\n","			",p_test1)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret11, ret12);
		test_ret++;
	}
	free(p_test1);
	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*p_test2 = NULL;
	printf("Printing addr %p with a null pointer : \n", p_test2);
	if ((ret13 = ft_printf("%s%p\n","			",p_test2)) != (ret14 = printf("%s%p\n","			",p_test2)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret13, ret14);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	char	*p_test3;
	printf("Printing addr %p flag and a non assigned pointer : \n", p_test3);
	if ((ret15 = ft_printf("%s%p\n","			",p_test3)) != (ret16 = printf("%s%p\n","			",p_test3)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret15, ret16);
		test_ret++;
	}


	return (test_ret);
}

int		test_c(void)
{
	printf(MAG"||---------------------- NOW TESTING WITH CHARS AND WIDE CHARS ------------------||\n"RESET);

	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;
	int		ret3 = 0;
	int		ret4 = 0;
	int		ret5 = 0;
	int		ret6 = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	char c_test1 = 48;
	printf("Testing simple conversion with char %c : \n", c_test1);
	if ((ret1 = ft_printf("%s%c\n","			",c_test1)) != (ret2 = printf("%s%c\n","			",c_test1)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret1, ret2);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	wchar_t c_test2 = 0x1234;
	printf("Testing simple conversion with char %C : \n", c_test2);
	if ((ret3 = ft_printf("%s%C\n","			",c_test2)) != (ret4 = printf("%s%C\n","			",c_test2)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret3, ret4);
		test_ret++;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	char c_test3 = 0;
	printf("Testing simple conversion with char %c ('\\0') : \n", c_test1);
	if ((ret5 = ft_printf("%s%c\n","			",c_test3)) != (ret6 = printf("%s%c\n","			",c_test3)))
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret5, ret6);
		test_ret++;
	}

	return (test_ret);
}

int		test_b(void)
{
	printf(MAG"||---------------------- NOW TESTING WITH BINARY REP ------------------||\n"RESET);

	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		b_test1 = 1;
	ft_printf("%s%b\n","			", b_test1);
	return (0);
}

int		test_flags(void)
{
	printf(MAG"||---------------------- NOW TESTING OPTS AND FLAGS ------------------||\n"RESET);
	int		test_ret = 0;
	int		ret1 = 0;
	int		ret2 = 0;
	int		ret3 = 0;
	int		ret4 = 0;
	int		ret5 = 0;
	int		ret6 = 0;
	int		ret7 = 0;
	int		ret8 = 0;
	int		ret9 = 0;
	int		ret11 = 0;
	int		ret12 = 0;
	int		ret13 = 0;
	int		ret14 = 0;
	int		ret15 = 0;
	int		ret16 = 0;
	int		ret17 = 0;
	int		ret18 = 0;
	int		ret19 = 0;
	int		ret20 = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		opt_test1 = 42;
	printf("All opt with %%d :\n");
	ret1 = ft_printf("%s%#010-+ .4d\n","			", opt_test1);
	ret2 = printf("%s%#010-+ .4d\n","			", opt_test1);
	if (ret1 != ret2)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret1, ret2);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		opt_test2 = 42;
	printf("All opt but - with %%d :\n");
	ret3 = ft_printf("%s%#010+ .4d\n","			", opt_test2);
	ret4 = printf("%s%#010+ .4d\n","			", opt_test2);
	if (ret3 != ret4)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret3, ret4);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		opt_test3 = 42;
	printf("Precision redefined multiple times : \n");
	ret5 = ft_printf("%s%.10.5.4.8d\n","			", opt_test3);
	ret6 = printf("%s%.10.5.4.8d\n","			", opt_test3);
	if (ret5 != ret6)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret5, ret6);
		test_ret++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	int		opt_test4 = 42;
	printf("All opt with %%x (PRINT THE REAL PRINTF BEFORE MY PRINTF):\n");
	ret7 = ft_printf("%s%#010-+ .4x%#010+ .4d\n","			", opt_test4, opt_test1);
	ret8 = printf("%s%#010-+ .4x%#010+ .4d\n","			", opt_test4, opt_test1);
	if (ret7 != ret8)
	{
		printf("Ret from FT_PRINTF is %d, it should be %d\n", ret7, ret8);
		test_ret++;
	}
	return (test_ret);
}

void	random_test_behavior(void)
{
	printf(MAG"||---------------------- SANDBOX ------------------||\n"RESET);
	setlocale(LC_ALL, "");
	int		ret1;
	int		ret2;
	int		ret3;
	int		ret4;

	ft_printf("%.25k\n");
	printf("%.25k\n");
	printf("-------------------------------\n");
	ft_printf("%.25%\n");
	printf("%.25%\n");
	printf("-------------------------------\n");
	ft_printf("@moulitest: %.o\n", 0);
	printf("@moulitest: %.o\n", 0);
	printf("-------------------------------\n");
	ft_printf("@moulitest: %#.o %#.0o\n", 0, 0);
	printf("@moulitest: %#.o %#.0o\n", 0, 0);
	printf("-------------------------------\n");
	ft_printf("@moulitest: %#.x %#.0x\n", 0, 0);
	printf("@moulitest: %#.x %#.0x\n", 0, 0);
	printf("-------------------------------\n");
	ft_printf("@moulitest: %.o %.0o\n", 0, 0);
	printf("@moulitest: %.o %.0o\n", 0, 0);
	printf("-------------------------------\n");
	ft_printf("@moulitest: %5.o %5.0o\n", 0, 0);
	printf("@moulitest: %5.o %5.0o\n", 0, 0);
	printf("-------------------------------\n");
	ret1 = ft_printf("{% +d}\n", 42);
	ret2 = printf("{% +d}\n", 42);
	printf("%d\n%d\n", ret1, ret2);
	printf("-------------------------------\n");
	ret3 = ft_printf("%.0p, %.p\n", "lol", "lol");
	ret4 = printf("%.0p, %.p\n", "lol", "lol");
	printf("%d\n%d\n", ret3, ret4);
	printf("-------------------------------\n");
	printf("[%s]\n", ft_unsigned_itoa_base(42, 10));
	printf("-------------------------------\n");
	ft_printf("%lld\n",-9223372036854775808);
	printf("%lld\n",-9223372036854775808);
	printf("-------------------------------\n");
	ret1 = ft_printf("%.4s\n", "42");
	ret2 = printf("%.4s\n", "42");
	printf("%d\n%d\n", ret1, ret2);
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%"));
	printf("%d\n", printf("%"));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%#o\n", 0));
	printf("%d\n", printf("%#o\n", 0));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("[%4.S]\n", L"我是一只猫。"));
	printf("%d\n", printf("[%4.S]\n", L"我是一只猫。"));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("[%15.4S]\n", L"我是一只猫。"));
	printf("%d\n", printf("[%15.4S]\n", L"我是一只猫。"));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("[%.4S]\n", L"我是一只猫。"));
	printf("%d\n", printf("[%.4S]\n", L"我是一只猫。"));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%ld\n", (long)INT_MIN - 1));
	printf("%d\n", printf("%ld\n", (long)INT_MIN - 1));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%ld\n", LONG_MIN));
	printf("%d\n", printf("%ld\n", LONG_MIN));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%lli\n", LLONG_MIN));
	printf("%d\n", printf("%lli\n", LLONG_MIN));
	printf("-------------------------------\n");
	printf("%d\n",ft_printf("%l"));
	printf("%d\n",printf("%l"));
	printf("-------------------------------\n");
	printf("%d\n",ft_printf("%+"));
	printf("%d\n",printf("%+"));
	printf("-------------------------------\n");
	printf("%d\n",ft_printf("%"));
	printf("%d\n",printf("%"));
	printf("-------------------------------\n");
	printf("%d\n",ft_printf("%o %ho %hho\n", -42, -42, -42));
	printf("%d\n",printf("%o %ho %hho\n", -42, -42, -42));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%#.3o\n", 1));
	printf("%d\n", printf("%#.3o\n", 1));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%.3o\n", 1));
	printf("%d\n", printf("%.3o\n", 1));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%#.3o\n", 0));
	printf("%d\n", printf("%#.3o\n", 0));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%c\n", 200));
	printf("%d\n", printf("%c\n", 200));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%C\n", 203));
	printf("%d\n", printf("%C\n", 203));
	printf("-------------------------------\n");
	printf("%d\n", ft_printf("%*d\n", 10, 42));
	printf("%d\n", printf("%*d\n", 10, 42));
	printf("%d\n", ft_printf("%10d\n", 42));
}

int		main(int ac, char *av[])
{
	printf(CYN"Note that the first string displayed is from the tested fonction FT_PRINTF.\n"RESET);
	int		overall_ret;
	int		(**f)(void);
	int		nb_fonction = 8;
	int		failed_test[10];
	int		i = 0;
	int		k = 0;
	int		j = 0;
	setlocale(LC_ALL, "");

	ft_memset(failed_test, 0, 10);
	f = malloc(sizeof(void*) * nb_fonction);
	overall_ret = 0;
	f[0] = test_s;
	f[1] = test_d;
	f[2] = test_o;
	f[3] = test_u;
	f[4] = test_x;
	f[5] = test_c;
	f[6] = test_b;
	f[7] = test_flags;
	while (i != nb_fonction)
	{
		if (((f)[i]()) != 0)
		{
			failed_test[j] = i;
			j++;
			overall_ret++;
			printf(RED"Test index %d not working\n"RESET, i);
		}
		else
			printf(GRN"Test index %d working \n"RESET, i);
		i++;
	}
	test_s();
	random_test_behavior();
	printf(CYN"||------------------------------RECAP--------------------------------||\n"RESET);
	if (overall_ret != 0)
	{
		printf(RED"You failed %d tests\n"RESET, overall_ret);
		printf(CYN"Index of the tests you failed :\n"RESET);
		while (k != j)
		{
			printf("- Test %d\n",  failed_test[k]);
			k++;
		}
	}
	else
		printf(GRN"RET VALUES ARE OK :O \\o/ \n"RESET);
	free(f);
	return (0);
}
