#include "hash_table.h"
#include "environ.h"
#include "libft.h"
#include "local.h"
#include "failure.h"

void	env_add_var(t_env *env, const char *key, const char *value)
{
	char		**environ;
	char		**new_environ;
	char		*new_key_value;
	char		*local_value;
	size_t		new_environ_size;

	if (ft_str_isdigit(key) || ft_strequ(key, "@") || ft_strequ(key, "*") || ft_strequ(key, "#") || ft_strequ(key, "?") || ft_strequ(key, "-") || ft_strequ(key, "$") || ft_strequ(key,"!"))
	{
		dprintf(2, "%s: ", key);
		investigate_error(1, "Wrong assignement :", "key cannot be fully numeric or contain reserved symbols", 0);
		return ;
	}
	environ = env->environ;
	new_environ_size = env->environ_size + 1;
	new_environ = palloc(sizeof(char*) * (new_environ_size + 1));
	new_key_value = ft_strsurround(key, "=", value);
	ft_memcpy(new_environ, environ, env->environ_size * sizeof(*new_environ));
	new_environ[new_environ_size - 1] = new_key_value;
	new_environ[new_environ_size] = NULL;
	free(env->environ);
	env->environ = new_environ;
	env->environ_size++;
	local_value = local_get_value(env->local, key);
	if (!local_value || (local_value && !ft_strequ(local_value, value)))
		local_add_change_from_string(env, new_key_value);
}

void	env_reload_tree_hash(t_env *env)
{
	free_ternary_tree(env->tree);
	env->tree = NULL;
	create_ternary_tree(env);
	free_hash_table(&env->hash_table);
	env->hash_table = NULL;
	create_hash_table(&env->hash_table, env->environ);
}

#include <stdio.h>
void	env_change_value(t_env *env, const char *key, size_t key_index, \
		const char *new_value)
{
	char	**environ;

	environ = env->environ;
	free(environ[key_index]);
	environ[key_index] = ft_strsurround(key, "=", new_value);
	local_add_change_from_key_value(env, key, new_value);
}

void	env_add_change(t_env *env, const char *key, const char *value)
{
	size_t	index;
	char	*curr_val;

	curr_val = env_getenv((const char**)env->environ, key, &index);
	if (curr_val == NULL)
		env_add_var(env, key, value);
	else
		env_change_value(env, key, index, value);
}

void	env_add_var_from_string(t_env *env, char *key_value, \
		ssize_t eq_index)
{
	key_value[eq_index] = '\0';
	env_add_change(env, (const char*)key_value, \
			(const char*)key_value + eq_index + 1);
	key_value[eq_index] = '=';
}
