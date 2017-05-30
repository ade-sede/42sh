#include "libft.h"

int		ft_is_hex(int c)
{
	if ((c >= 'A' && c <= 'F') || ft_isdigit(c) || (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}
