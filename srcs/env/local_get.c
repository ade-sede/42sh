#include "local.h"

/*
**	Returns an allocated string containing the value of a local found with the key data.
*/

char	*local_get_var(t_list *local, char *key_want)
{
	char	*key;

	while (local != NULL)
	{
		key = key_of_local(local->data, '=');
		if (ft_strcmp(key_want, key) == 0)
		{
			free(key);
			return (value_of_local(local->data, '='));
		}
		free(key);
		local = local->next;
	}
	return (NULL);
}

/*
**	Given a string data, returns a malloc'ed string containing everything
**	from the start of data up to c
*/

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

/*
**	same as above, but returns value instead of key
*/

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
