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

int	local_add_change_from_key_value(t_local_list **first, const char *key, const char *value)
{
	return (1);
}
