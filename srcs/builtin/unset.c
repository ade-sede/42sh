#include "t_env.h"
#include "builtin.h"
#include "local.h"

int		builtin_unset(t_env *env, const char **argv)
{
	size_t	x;

	if (ft_arraylen(argv) == 1)
		return (EXIT_FAILURE);
	x = 1;
	while (argv[x] != NULL)
	{
		if (!env->local)
			break ;
		remove_var_from_local(&env->local, (char*)argv[x]);
		x++;
	}
	return (EXIT_SUCCESS);
}
