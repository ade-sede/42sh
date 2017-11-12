#include "local.h"
#include "libft.h"

int		local_add_from_key_value(t_local_list **first, const char *key, const char *value)
{
	t_local_list	*local;

	local = create_local(key, value);
	ft_genlst_pushback(first, local);
	return (1);
}

int		local_add_from_string(t_local_list **first, const char *string)
{
	char	tmp;
	char	*pos;

	pos = ft_strchr(string, '=');
	if (pos == NULL)
		return (0);
	tmp = *pos;
	*pos = 0;
	local_add_from_key_value(first, string, pos + 1);
	*pos = tmp;
	return (1);
}	

int		local_add_change_from_key_value(t_local_list **first, const char *key, const char *value)
{
	t_local_list	*node;

	if ((node = local_get_node(*first, key)))
		node->value = (char*)value;
	else
		local_add_from_key_value(first, key, value);
	return (1);
}

int		local_add_change_from_string(t_local_list **first, const char *string)
{
	size_t	pos;
	t_local_list	*node;
	char	*little_key;

	pos = ft_strichr(string, '=');
	little_key = ft_strsub(string, 0, pos + 1);
	if ((node = local_get_node(*first, little_key)))
		local_add_from_key_value(first, little_key, string + pos + 1);
	else
		local_add_from_string(first, string);
	free(little_key);
	return (1);
}
