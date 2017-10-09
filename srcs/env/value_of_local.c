#include "local.h"

char	*value_of_local(char *data, int c)
{
	int		pos_egale;
	int		len_value;
	char	*value;

	if ((pos_egale = ft_strichr(data, c)) == -1)
		return (NULL);
	len_value = ft_strlen(data + pos_egale + 1);
	if ((value = ft_memalloc(sizeof(*value) * (len_value))) == NULL)
		return (NULL);
	ft_memcpy(value, data + pos_egale + 1, len_value);
	value[len_value] = '\0';
	return (value);
}
