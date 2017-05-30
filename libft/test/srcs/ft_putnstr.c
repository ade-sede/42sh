#include "libft.h"

void	ft_putnstr(char *str, size_t len)
{
	write(1, str, len);
}
