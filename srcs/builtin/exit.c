#include "libft.h"
#include "t_env.h"
#include "local.h"
#include "builtin.h"
#include "failure.h"
#include "history.h"

int	builtin_exit(t_env *env, const char **argv)
{
	int		exit_status;
	int		argc;

	argc = ft_arraylen(argv);
	exit_status = ft_atoi(local_get_value(env->local, "$?"));
	if (argc == 1)
	{
		history_write_to_histfile();
		exit(exit_status);
	}
	if (argc > 2)
		return (investigate_error(1, NULL, "exit: to many arguments",
					EXIT_FAILURE));
	else if (!(ft_atoi_safe(argv[1], &exit_status)))
		return (investigate_error(1, NULL, "exit: numeric argument required",
					EXIT_FAILURE));
	else
	{
		history_write_to_histfile(NULL, NULL);
		conf_term_canonical();
		exit(exit_status);
	}
	return (EXIT_SUCCESS);
}
