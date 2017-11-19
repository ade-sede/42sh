#include "libft.h"
#include "local.h"

int		local_remove(t_env *env, const char *key)
{
	t_list *node;

	node = local_get_node(env->local, key);
	if (node)
		ft_simple_lst_del_one(&env->local, node, free_local);
	return (1);
}
