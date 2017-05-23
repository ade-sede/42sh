#include "libft.h"
#include "env.h"

int	return_failure(const char *str, const char *error_msg)
{
	if (str)
		ft_putstr(str);
	if (error_msg)
		ft_putstr(error_msg);
	ft_putchar('\n');
	return (EXIT_FAILURE);
}
