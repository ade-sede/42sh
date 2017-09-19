#include "env.h"
#include "libft.h"
#include <unistd.h>

int		builtin_setenv(t_env *env, const char **argv)
{
	int		eq_index;
	int		i;
	int		argc;

	argc = ft_arraylen(argv);
	if (argc == 1)
		env_print_environ((const char **)env->environ);
	i = 1;
	while (i < argc)
	{
		eq_index = ft_strichr(argv[i], '=');
		if (eq_index != -1 && eq_index != 0)
		{
			env_add_var_from_string(env, (char*)argv[i], eq_index);
			if (ft_strnequ(argv[i], "PATH", 4))
				env_reload_tree_hash(env);
		}
		else
		{
			return (return_failure("usage: setenv key1=value1 key2=value2 ..",\
						NULL));
		}
		i++;
	}
	return (0);
}
