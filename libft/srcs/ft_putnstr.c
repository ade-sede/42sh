#include "libft.h"

static size_t size_t_min(size_t a, size_t b)
{
	return ((a < b) ? a : b);
}

void	ft_putnstr(char *str, size_t len)
{
	len = size_t_min(ft_strlen(str), len);
	write(1, str, len);
}
