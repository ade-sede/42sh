#include "libft.h"

int		ft_ishex(int c)
{
	if ((c >= 'A' && c <= 'F') || ft_isdigit(c) || (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}
