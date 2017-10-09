#include "local.h"
#include "builtin.h"
#include "env.h"

int			builtin_set(t_env *env, const char **argv)
{
	t_list	*tmp_list;

	(void)argv;
	tmp_list = env->local;
	while (tmp_list != NULL)
	{
		ft_putendl(tmp_list->data);
		tmp_list = tmp_list->next;
	}
	return (EXIT_SUCCESS);
}
