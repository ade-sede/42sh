#include "libft.h"
#include "failure.h"

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
