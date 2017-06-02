#include "libft.h"
#include "array.h"

static size_t ft_max_size_t(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}

size_t	ft_arraymax_f(const char **str, size_t (*f)(const char *))
{
	size_t	max;

	max = 0;
	while (*str)
	{
		max = ft_max_size_t(f(*str), max);
		str++;
	}	
	return (max);
}
