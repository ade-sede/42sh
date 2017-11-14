#include "libft.h"
#include "environ.h"
#include "printf.h"
#include "hash_table.h"
#include "local.h"

void		env_load_base_env(t_env *env, const char **environ)
{
	size_t	i;
	char	*pid_string;

	i = 0;
	env->environ = NULL;
	env->previous_exit = 0;
	env->option = 0;
	env->alias = NULL;
	env->first_func = NULL;
	env->pos_param = NULL;
	env->local = NULL;
	env->environ = env_create_environ(environ, &(env->environ_size));
	env_load_shlvl_pwd(env);
	while (i != env->environ_size)
	{
		local_add_change_from_string(&env->local, env->environ[i]);
		++i;
	}
	pid_string = ft_itoa_base(getpid(), 10);
	local_add_change_from_key_value(&env->local, "$", pid_string);
	free(pid_string);
	create_hash_table(&env->hash_table, env->environ);
}

void		env_load_shlvl_pwd(t_env *env)
{
	char		buf[PATH_MAX];
	size_t		index;
	char		*new_entry;

	if (env_getenv((const char**)env->environ, "PWD", &index) == NULL)
		env_add_var(env, "PWD", getcwd(buf, PATH_MAX));
	if (env_getenv((const char **)env->environ, "SHLVL", &index) == NULL)
		env_add_var(env, "SHLVL", "1");
	else
	{
		new_entry = ft_itoa_base(ft_atoi((env->environ)[index] + 6) + 1, 10);
		env_change_value(env, "SHLVL", index, new_entry);
		free(new_entry);
	}
	env_add_change(env, "SHELL", "42sh");
	if (!env_getenv((const char **)env->environ, "HISTFILE", NULL))
		env_add_change(env, "HISTFILE", "42sh_history");
}
