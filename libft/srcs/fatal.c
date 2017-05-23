#include "libft.h"
#include "printf.h"

void	fatal(const char *error_str)
{
	if (error_str != NULL)
		ft_printf("%s\n", error_str);
	exit(1);
}
