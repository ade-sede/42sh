#include "libft.h"
#include "failure.h"
#include <stdio.h>
#include <stdarg.h>
#include "color.h"

char	*singleton_error(void)
{
	static char	buff[E_BUFSIZE];

	return (buff);
}

int		return_failure(const char *str, const char *error_msg)
{
	if (str)
		ft_putstr_fd(str, 2);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}

int		get_logfd(const char *file)
{
	int			fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}


int		logwrite(const char *filename, const char *func_name,
									const char *format, ...)
{
	va_list		ap;
	int			fd;
	time_t		rawtime;
	struct tm	*info;
	char		time_str[26];

	time(&rawtime);
	info = localtime(&rawtime);
	fd = get_logfd(filename);
	strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", info);
	if (fd >= 0)
	{
		va_start(ap, format);
		dprintf(fd, "From "GRN"%s "RESET" @ %s"BLU"##\n"RESET,
										func_name, time_str);
		vdprintf(fd, format, ap);
		dprintf(fd, BLU"##\n"RESET);
		va_end(ap);
		close(fd);
		return (1);
	}
	return (-1);
}


int		investigate_error(int log, const char *prefix,
							const char *custom_error, int return_value)
{
	size_t		i;
	char		*buff;
	char		*error_name;

	buff = singleton_error();
	ft_bzero(buff, E_BUFSIZE);
	if (prefix != NULL && (i = -1))
	{
		while (prefix[++i])
			buff[i] = prefix[i];
		buff[i++] = ':';
		buff[i++] = ' ';
		error_name = custom_error ? (char*)custom_error : get_errno();
		if (error_name)
			ft_strcpy(buff + i, error_name);
	}
	else if (custom_error != NULL && prefix == NULL)
		ft_strcpy(buff, custom_error);
	if (log)
		ft_putendl_fd(buff, 2);
	return (return_value == -1 ? errno : return_value);
}
/*
**	if (!log)
**		logwrite(logfile, __func__, "%s\n", buff);
*/
