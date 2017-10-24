#include "local.h"

static t_list	*find_key(t_list *local, char *new_key)
{
	char	*key;

	while (local != NULL)
	{
		key = key_of_local(local->data, '=');
		if (ft_strcmp(new_key, key) == 0)
		{
			free(key);
			return (local);
		}
		free(key);
		local = local->next;
	}
	return (NULL);
}

int				remove_var_from_local(t_list **local, char *key)
{
	t_list	*match_key;

	if ((match_key = find_key(*local, key)) != NULL)
	{
		ft_simple_lst_del_one(local, match_key, ft_free);
		return (1);
	}
	return (0);
}
