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
	if (!ft_atoi_safe(local_get_value(env->local, "?"), &exit_status))
		exit_status = 1;
	if (argc == 1)
	{
		//ft_putstr_fd("exit\n", 2);
		if (isatty(STDIN_FILENO))
			conf_term_canonical();
		history_write_to_histfile();
		exit(exit_status);
	}
	if (argc > 2)
		return (investigate_error(1, NULL, "exit: too many arguments",
					EXIT_FAILURE));
	else if (!(ft_atoi_safe(argv[1], &exit_status)))
	{
		history_write_to_histfile();
		if (isatty(STDIN_FILENO))
			conf_term_canonical();
		exit(investigate_error(1, "exit: numeric argument required", argv[1],
					255));
	}
	else
	{
		history_write_to_histfile();
		if (isatty(STDIN_FILENO))
			conf_term_canonical();
		exit(exit_status);
	}
	return (EXIT_SUCCESS);
}
