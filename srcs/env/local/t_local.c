#include "local.h"
#include "libft.h"

t_local_list	*create_local(const char *key, const char *value)
{
	t_local_list	*local;

	local = palloc(sizeof(*local));
	local->key = ft_strdup(key);
	local->value = ft_strdup(value);
	return (local);
}
