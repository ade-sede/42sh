#include "t_env.h"
#include "builtin.h"
#include "exec.h"
#include "read.h"
#include <sys/wait.h>
#include <fcntl.h>

static t_builtin	g_builtin[] =
{
	{"cd", &builtin_cd},
	{"exit", &builtin_exit},
	{"env", &builtin_env},
	{"unsetenv", &builtin_unsetenv},
	{"setenv", &builtin_setenv},
	{"echo", &builtin_echo},
	{"alias", &builtin_alias},
	{"unalias", &builtin_unalias},
	{"fg", &builtin_fg},
	{"bg", &builtin_bg},
	{"jobs", &builtin_jobs},
	{"set", &builtin_set},
	{"unset", &builtin_unset},
	{"shopt", &builtin_shopt},
	{"shift", &builtin_shift},
	{"export", &builtin_export},
	{"read", &builtin_read},
	{"history", &builtin_history},
	{NULL, NULL}
};

void		*get_exec_builtin(const char *cmd)
{
	int			i;

	i = 0;
	while (g_builtin[i].key && !ft_strequ(g_builtin[i].key, cmd))
		i++;
	return (g_builtin[i].f);
}

int			exec_builtin(t_env *env, const char **argv)
{
	int			(*f)(t_env*, const char**);

	if ((f = get_exec_builtin(argv[0])) == NULL)
		return (EXIT_FAILURE);
	return (f(env, argv));
}
