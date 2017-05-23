#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*little_str;
	size_t	i;

	i = 0;
	if ((little_str = (char*)malloc(sizeof(char) * len + 1)) == NULL || !s)
		return (NULL);
	while (i != len)
	{
		little_str[i] = s[start];
		start++;
		i++;
	}
	little_str[i] = '\0';
	return (little_str);
}
