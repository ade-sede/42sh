#include "libft.h"
#include "env.h"
#include "builtin.h"

t_builtin g_builtin[] = 
{ 
	{"cd", &builtin_cd},
	{"exit", &builtin_exit},
	{"env", &builtin_env},
	{"unsetenv", &builtin_unsetenv},
	{"setenv", &builtin_setenv},
	{"echo", &builtin_echo},
	{"history", &builtin_history},
	{NULL, NULL}
};

int		exec_builtin(t_env *env, const char **argv)
{
	int	i;

	i = 0;
	while (g_builtin[i].key)
	{
		if (ft_strequ(g_builtin[i].key, argv[0]))
		{
			env->previous_exit = g_builtin[i].f(env, argv);
			return (1);
		}
		i++;
	}
	return (0);
}
