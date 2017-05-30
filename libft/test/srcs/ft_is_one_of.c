#include "libft.h"

int		ft_is_one_of(char c, const char *that)
{
	int	i;

	i = 0;
	while (that[i])
	{
		if (c == that[i])
			return (1);
		i++;
	}
	return (0);
}
