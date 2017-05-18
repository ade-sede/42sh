#include "minishell.h"
#include "libft.h"

void	env_remove_var(t_env *env, char *var)
{
	int	index;

	if (env_getenv(env->environ, argv[i], &index))
		env_remove_var_index(env, index);
}
