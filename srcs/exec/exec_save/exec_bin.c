#include "exec.h"
#include "libft.h"
#include "env.h"
#include "sys/wait.h"
#include "exec.h"
#include "hash_table.h"
#include "failure.h"
#include "my_signal.h"

/*
**		We forked, this is called in the child process. Try to use the absolute
**		path to the binary.
*/

static void		exec_bin_absolute(t_env *env, const char **argv)
{
	if (access(argv[0], F_OK) == -1)
		exit(investigate_error(1, argv[0], "no such file or directory",
					EXIT_FAILURE));
	else if (access(argv[0], X_OK) == -1)
		exit(investigate_error(1, argv[0], "permission denied ",
					EXIT_FAILURE));
	else if (execve(argv[0], (char**)argv, env->environ) == -1)
		exit(investigate_error(1, argv[0], "command not found",
					EXIT_FAILURE));
	exit(1);
}

/*
**		We forked, this is called in the child process. Looks for the binary in
**		the path, exit_failure if we cant find id.
*/

static void		exec_bin_path(t_env *env, const char **argv)
{
	char	*bin;

	if (!(bin = hash_get(env->hash_table, (char *)argv[0])))
		exit(investigate_error(1, argv[0], "command not found",
					EXIT_FAILURE));
	if (access(bin, F_OK) == 0)
	{
		if (access(bin, X_OK) == -1)
			exit(investigate_error(1, bin, "permission denied ",
						EXIT_FAILURE));
		else if (execve(bin, (char**)argv, env->environ) == -1)
			exit(investigate_error(1, argv[0], "command not found",
						EXIT_FAILURE));
	}
	exit(investigate_error(1, (const char *)*argv, "commmand not found",
				EXIT_FAILURE));
}

int			exec_bin(t_env *env, const char **argv)
{
	ft_strchr(argv[0], '/') ? exec_bin_absolute(env, argv) : \
			exec_bin_path(env, argv);
	return (1);
}

/*
**		if (WIFSIGNALED(ret) == 1)
**				return (env->previous_exit = WEXITSTATUS(ret));
**		return (exec_bin_no_fork(env, argv));
*/
