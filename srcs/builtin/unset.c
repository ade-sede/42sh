#include "t_env.h"
#include "builtin.h"
#include "local.h"

int		builtin_unset(t_env *env, const char **argv)
{
	size_t	x;

	if (ft_arraylen(argv) == 1)
		return (EXIT_FAILURE);
	x = 1;
	while (argv[x] && env->local)
	{
		local_remove(&env->local, argv[x]);
		++x;
	}
	return (EXIT_SUCCESS);
}
