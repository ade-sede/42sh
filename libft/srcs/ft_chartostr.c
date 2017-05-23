#include "libft.h"

char	*ft_chartostr(char c)
{
	char	*str;

	str = malloc(2);
	str[0] = c;
	str[1] = 0;
	return (str);
}
