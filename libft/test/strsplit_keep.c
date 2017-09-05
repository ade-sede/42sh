#include "libft.h"
#include "alloc.h"
#include "string.h"
#include "color.h"
#include <stdio.h>

const char 	*casual_split_keep(short *error)
{
	char	*input = "~ lol mdr\n";
	char	**split;

	split = ft_strsplit_keep(input, WHITESPACES);
	while (*split)
	{
		printf(MAG"#"CYN"%s"MAG"#\n"RESET, *split);
		split++;
	}
	*error = FALSE;
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 1, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;

	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = casual_split_keep;
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
