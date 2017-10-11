#include "local.h"

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
