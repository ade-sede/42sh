#include "libft.h"

char	*ft_strndup(char *s1, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	if ((dest = ft_strnew(n + 1)) == NULL)
		return (NULL);
	while (s1[i] && i != n)
	{
		dest[i] = s1[i];
		i++;
	}
	return (dest);
}
