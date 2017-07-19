/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:47:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/19 17:22:45 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errno.h"
#include "fcntl.h"
#include "color.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#define WRITE_END 1
#define READ_END 0

const char	*test_dup2only_writefd(short *error)
{
	dprintf(2, CYN"\nLaunching test %s\n"RESET, __func__);
	char	*path;
	const char	*str;
	char	buff[4096];
	int		save_stdout;

	path = "test/dup2only_writefd.txt";
	str = __func__;

	int		fd = open(path, O_CREAT | O_RDWR);
	if (fd < 0)
		dprintf(2, RED"CANT OPEN\n"RESET);
	chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);

	/* Saving original fd 1, and dupping 1 onto fd such as if you try to access 1 you access fd instead */
	dprintf(2, "Before dup, fd = "BLU"%d\n"RESET, fd);
	save_stdout = dup(1);
	dup2(fd, 1);
	dprintf(2, "After dup, fd = "BLU"%d\n"RESET, fd);

	/* Print on fd*/
	ft_putstr_fd(str, fd);

	/* Reset needle. */
	close(fd);
	fd = open(path, O_CREAT | O_RDWR);
	if (fd < 0)
		dprintf(2, RED"CANT OPEN\n"RESET);
	/* Read into buff */
	read(fd, buff, 4096);

	/* Restoring fd */
	dup2(save_stdout, 1);
	fflush(stdout);
	close(save_stdout);
	/* Checking if fd 1 is still up */
	dprintf(1, " If this appears on standard output, we restored fd 1 successfully. This was called from %s\n", __func__);

	/* Cmp */
	if (strcmp(buff, str) != 0)
	{
		dprintf(2, "str = "MAG"#"CYN"%s"MAG"#\n", str);
		dprintf(2, "buff = "MAG"#"CYN"%s"MAG"#\n", buff);
		*error = TRUE;
	}
	else
		dprintf(2, MAG"#"CYN"%s"MAG"#\n"RESET, buff);
	close(fd);
	return (__func__);
}

const char	*test_dup2only_1(short *error)
{
	dprintf(2, CYN"\nLaunching test %s\n"RESET, __func__);
	char	*path;
	const char	*str;
	char	buff[4096];
	int		save_stdout;

	path = "test/dup2only_1.txt";
	str = __func__;


	int		fd = open(path, O_CREAT | O_RDWR);
	if (fd < 0)
		dprintf(2, RED"CANT OPEN\n"RESET);
	chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);

	/* Saving original fd 1, and dupping 1 onto fd such as if you try to access 1 you access fd instead */

	dprintf(2, "Before dup, fd = "BLU"%d\n"RESET, fd);
	save_stdout = dup(1);
	dup2(fd, 1);
	dprintf(2, "After dup, fd = "BLU"%d\n"RESET, fd);


	/* Print on fd 1*/
	ft_putstr_fd(str, 1);

	/* Reset needle. */
	close(fd);
	fd = open(path, O_CREAT | O_RDWR);
	if (fd < 0)
		dprintf(2, RED"CANT OPEN\n"RESET);
	/* Read into buff */
	read(fd, buff, 4096);

	/* Restoring fd */
	close(fd);
	dup2(save_stdout, 1);
	/* close(save_stdout); */
	/* Checking if fd 1 is still up */
	dprintf(1, " If this appears on standard output, we restored fd 1 successfully. This was called from %s\n", __func__);

	/* Cmp */
	if (strcmp(buff, str) != 0)
	{
		dprintf(2, "str = "MAG"#"CYN"%s"MAG"#\n", str);
		dprintf(2, "buff = "MAG"#"CYN"%s"MAG"#\n", buff);
		*error = TRUE;
	}
	else
		dprintf(2, MAG"#"CYN"%s"MAG"#\n"RESET, buff);
	return (__func__);
}

int	main(void)
{
	size_t nb_func = 2, index = 0;
	const char *error_list[nb_func + 1];
	short int error = FALSE, nb_error = 0;
	const char *(*f[nb_func])(short int*);
	const char	*func_ret;
	bzero(f, nb_func);
	bzero(error_list, nb_func + 1);
	f[0] = &test_dup2only_1;
	f[1] = &test_dup2only_writefd;
	while (index < nb_func)
	{
		error = FALSE;
		func_ret = f[index](&error);
		if (error)
		{
			dprintf(2, RED"FAIL @ %s\n"RESET, func_ret);
			error_list[nb_error] = func_ret;
			nb_error++;
		}
		else
			dprintf(2, GRN"SUCCESS @ %s\n"RESET, func_ret);
		index++;
	}
	if (nb_error)
	{
		dprintf(2, MAG"\nReminder of failed tests\n"RESET);
		for (int i = 0; i < nb_error; i++)
			dprintf(2, "- %s\n", error_list[i]);
	}
	return (0);
}
