#include "str.h"
#include "libft.h"

int		ft_str_is_clr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}
