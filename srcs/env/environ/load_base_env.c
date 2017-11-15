#include "libft.h"
#include "environ.h"
#include "printf.h"
#include "hash_table.h"
#include "local.h"

static int	load_color(t_env *env)
{
	local_add_change_from_key_value(&env->local, "word_color", RESET);
	local_add_change_from_key_value(&env->local, "default_color", RESET);
	local_add_change_from_key_value(&env->local, "comment_color", RESET);
	local_add_change_from_key_value(&env->local, "operator_color", RESET);
	local_add_change_from_key_value(&env->local, "param_exp_color", BLU);
	local_add_change_from_key_value(&env->local, "cmd_subst_color", RESET);
	local_add_change_from_key_value(&env->local, "dquotes_color", YEL);
	local_add_change_from_key_value(&env->local, "quotes_color", MAG);
	local_add_change_from_key_value(&env->local, "bs_color", CYN);
	return (1);
}

static int	load_special_params(t_env *env)
{
	char	*pid_string;
	char	*ppid_string;

	pid_string = ft_itoa_base(getpid(), 10);
	ppid_string = ft_itoa_base(getppid(), 10);
	local_add_change_from_key_value(&env->local, "$", pid_string);
	local_add_change_from_key_value(&env->local, "PID", pid_string);
	local_add_change_from_key_value(&env->local, "PPID", ppid_string);
	free(pid_string);
	free(ppid_string);
	return (1);
}

void		env_load_base_env(t_env *env, const char **environ)
{
	size_t	i;

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
	create_hash_table(&env->hash_table, env->environ);
	load_special_params(env);
	load_color(env);
}

void		env_load_shlvl_pwd(t_env *env)
{
	char		buf[PATH_MAX];
	size_t		index;
	char		*new_entry;
	char		*tmp;

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
	tmp = ft_gethome();
	if (tmp)
	{
		tmp = ft_strjoin(tmp, "/.42sh_history");
		env_add_change(env, "HISTFILE", tmp);
	}
	else
		env_add_change(env, "HISTFILE", "");
}
