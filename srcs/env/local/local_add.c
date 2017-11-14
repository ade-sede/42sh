#include "local.h"
#include "t_env.h"
#include "environ.h"
#include "libft.h"
#include "shopt.h"
#include <stdio.h>

int		local_add_from_key_value(t_list **first, const char *key, const char *value)
{
	t_local	*local;

	local = create_local(key, value);
	ft_simple_lst_pushback(first, ft_simple_lst_create(local));
	if (singleton_env()->option & ALLEXPORT)
	{
		env_add_change(singleton_env(), key, value);
	}
	return (1);
}

int		local_add_from_string(t_list **first, const char *string)
{
	char	tmp;
	char	*pos;

	pos = ft_strchr(string, '=');
	if (pos == NULL)
		return (0);
	tmp = *pos;
	*pos = 0;
	local_add_from_key_value(first, string, pos + 1); *pos = tmp;
	return (1);
}	

int		local_add_change_from_key_value(t_list **first, const char *key, const char *value)
{
	t_list	*node;
	t_local	*local;

	if ((node = local_get_node(*first, key)))
	{
		local = node->data;
		if (!ft_strequ(local->value, value))
			local->value = ft_strchange(local->value, ft_strdup(value));
	}
	else
		local_add_from_key_value(first, key, value);
	return (1);
}

int		local_add_change_from_string(t_list **first, const char *string)
{
	size_t	pos;
	t_list	*node;
	char	*little_key;

	pos = ft_strichr(string, '=');
	little_key = ft_strsub(string, 0, pos + 1);
	if ((node = local_get_node(*first, little_key)))
		local_add_change_from_key_value(first, little_key, string + pos + 1);
	else
		local_add_from_string(first, string);
	free(little_key);
	return (1);
}
