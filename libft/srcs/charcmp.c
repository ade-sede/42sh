#include "libft.h"
#include <stdio.h>

short int	charcmp(const char *str, size_t i, char c)
{
	int ret;

	ret = false;
	if (str[i] != c)
		return (false);
	else
		while (i != 0 && str[i - 1] == '\\')
		{
			i--;
			ret = (ret) ? 0 : 1;
		}
	if (ret)
		return (false);
	return (true);
}


