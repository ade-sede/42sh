#include "libft.h"

intmax_t	ft_abs(intmax_t value)
{
	return ((value >= 0) ? (long)value : (long)-(value));
}
