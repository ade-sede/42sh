#include "local.h"

static t_list	*find_key(t_list *local, char *new_data)
{
	char	*new_key;
	char	*key;

	new_key = key_of_local(new_data, '=');
	while (local)
	{
		key = key_of_local(local->data, '=');
		if (ft_strcmp(new_key, key) == 0)
		{
			free(new_key);
			free(key);
			return (local);
		}
		free(key);
		local = local->next;
	}
	free(new_key);
	return (NULL);
}

#include <stdio.h>

int				add_to_local(t_list **local, char *data)
{
	dprintf(2, "%p\n", *local);
	t_list	*match_key;
	t_list	*first;

	if ((match_key = find_key(*local, data)) == NULL)
		ft_simple_lst_pushback(local, ft_simple_lst_create(data));
	else
		match_key->data = ft_strchange(match_key->data, data);
	first = *local;
	while (*local)
	{
		dprintf(2, MAG"#"CYN"%s"MAG"#\n"RESET, (*local)->data);//			REMOVE		
		(*local) = (*local)->next;
	}
	*local = first;
	return (0);
}
