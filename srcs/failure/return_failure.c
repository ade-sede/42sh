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

FILE	*get_logfd(const char *file)
{
	const char	*f = NULL;
	FILE	*fp = NULL;

	if (!f || (f && !ft_strequ(f, file)))
	{
		f = file;
		if ((fp = fopen(file, "a+")) == NULL)
		{
			perror("fopen");
			return (NULL);
		}
	}
	return (fp);
}

int		logwrite(const char *filename, const char *func_name, const char *format, ...)
{
	va_list	ap;
	FILE	*fp;

	fp = get_logfd(filename);

	if (fp)
	{
		va_start(ap, format);
		fprintf(fp, "From "GRN"%s "BLU"##\n"RESET, func_name);
		vfprintf(fp, format, ap);
		fprintf(fp, BLU"##\n"RESET);
		fflush(fp);
		va_end(ap);
		fclose(fp);
	}
	return (1);
}

int			investigate_error(const char *prefix, const char *custom_error, int return_value)
{
	size_t	i;
	char	*buff;
	char	*error_name;

	buff = singleton_error();
	ft_bzero(buff, E_BUFSIZE);
	if (prefix != NULL)
	{
		i = 0;
		while (prefix[i])
		{
			buff[i] = prefix[i];
			i++;
		}
		buff[i++] = ':';
		buff[i++] = ' ';
		error_name = custom_error ? (char*)custom_error : get_errno();
		if (error_name)
			ft_strcpy(buff + i, error_name);
	}
	else if (custom_error != NULL && prefix == NULL)
		ft_strcpy(buff, custom_error);
	ft_putendl_fd(buff, 2);
	return (return_value == -1 ? errno : return_value);
}
