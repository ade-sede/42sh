#include "libft.h"
#include "env.h"
#include "sys/wait.h"
#include "exec.h"
#include <errno.h>
#include "hash_table.h"

/*
**		We forked, this is called in the child process. Try to use the absolute
**		path to the binary.
*/

void		ft_exec_bin_absolute(t_env *env, const char **argv)
{
	if (access(argv[0], F_OK) == -1)
		exit(return_failure(argv[0], " :no such file or directory"));
	else if (access(argv[0], X_OK) == -1)
		exit(return_failure(argv[0], " :permission denied "));
	else if (execve(argv[0], (char**)argv, env->environ) == -1)
		exit(return_failure(argv[0], " :command not found"));
	exit(1);
}

/*
**		We forked, this is called in the child process. Looks for the binary in
**		the path, exit_failure if we cant find id.
*/

void		ft_exec_bin_path(t_env *env, const char **argv)
{
	char	*bin;

	if (!(bin = hash_get(env->hash_table, (char *)argv[0])))
		exit(return_failure(argv[0], " :command not found"));
	if (access(bin, F_OK) == 0)
	{
		if (access(bin, X_OK) == -1)
		{
			exit(return_failure(bin, " :permission denied "));
		}
		else if (execve(bin, (char**)argv, env->environ) == -1)
		{
			exit(return_failure(argv[0], " :command not found"));
		}
	}
	exit(return_failure((const char *)*argv, " :commmand not found"));
}

int			fork_exec_bin(t_env *env, const char **argv, t_lst_head *head)
{
	t_list_d	*cur;
	t_pipe		*pr;
	t_pipe		*pl;
	int			ret;

	cur = (head) ? head->middle : NULL;
	pr = (cur != NULL) ? cur->data : NULL;
	pl = (cur && cur->prev) ? cur->prev->data : NULL;

	pid_t		child;
	no_handle_signals();
	if ((pl && !pr) || (!pl && !pr))
	{
		if ((child = fork()) == 0)
		{
			ft_strchr(argv[0], '/') ? ft_exec_bin_absolute(env, argv) : \
				ft_exec_bin_path(env, argv);
		}
		if (child > 0)
		{
			env->child_pid = child;
			waitpid(child, &ret, WUNTRACED);
			return (env->previous_exit = WEXITSTATUS(ret));
		}
	}
	else
	{
		ft_strchr(argv[0], '/') ? ft_exec_bin_absolute(env, argv) : \
			ft_exec_bin_path(env, argv);
	}
	return (1);
}
