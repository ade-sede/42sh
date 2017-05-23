#include "libft.h"

ssize_t		ft_strichr(const char *s, char c)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

ssize_t		ft_arrayichr(const char **array, const char *str)
{
	ssize_t	i;

	i = 0;
	if (!array || !str)
		return (-1);
	while (array[i] && !ft_strequ(array[i], str))
		i++;
	if (array[i])
		return (i);
	return (-1);
}
