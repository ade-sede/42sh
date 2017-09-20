#include "env.h"
#include "libft.h"
#include "failure.h"

int	builtin_unsetenv(t_env *env, char **argv)
{
	size_t	i;
	size_t	argc;

	argc = ft_arraylen((const char**)argv);
	if (argc == 1)
		return (investigate_error(NULL, "unsetenv: Too few arguments\n", EXIT_FAILURE));
	i = 1;
	while (i < argc)
	{
		env_remove_var(env, argv[i]);
		if (ft_strequ(argv[i], "PATH"))
			env_reload_tree_hash(env);
		i++;
	}
	return (EXIT_SUCCESS);
}
