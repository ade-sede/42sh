#include "local.h"

char	*key_of_local(char *data, int c)
{
	int		pos_egale;
	char	*key;

	if ((pos_egale = ft_strichr(data, c)) == -1)
		return (NULL);
	if ((key = ft_memalloc(sizeof(*key) * (pos_egale + 1))) == NULL)
		return (NULL);
	ft_memcpy(key, data, pos_egale);
	key[pos_egale] = '\0';
	return (key);
}
