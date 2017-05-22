#include "libft.h"

size_t	ft_arraylen(char **str)
{
	char **tmp;

	tmp = str;
	while (*str)
		str++;
	return (str - tmp);
}
