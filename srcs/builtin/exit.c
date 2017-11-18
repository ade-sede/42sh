#include "libft.h"
#include "t_env.h"
#include "local.h"
#include "builtin.h"
#include "failure.h"
#include "history.h"


static int	ft_isnum(char *str)
{
	char	*beg;

	if (!(beg = str))
		return (0);
	while (str && *str && *str >= 0 && *str <= 9)
		str++;
	if(str && *str && str != beg)
		return (1);
	return (0);
}

static int	ft_getstat(t_env *env, char *str)
{
	if(!str)
		return (0);
	if(ft_isnum(str))
		return ft_atoi(local_get_value(env->local, "$?"));
	return (255);
}

int	builtin_exit(t_env *env, const char **argv)
{
	int		exit_status;
	int		argc;

	argc = ft_arraylen(argv);
	//exit_status = ft_isnum(local_get_value(env->local, "$?")) ? ft_atoi(local_get_value(env->local, "$?")) : 255;
	exit_status = ft_getstat(env, local_get_value(env->local, "$?"));
	if (argc == 1)
	{
		//ft_putstr_fd("exit\n", 2);
		history_write_to_histfile();
		exit(exit_status);
	}
	if (argc > 2)
		return (investigate_error(1, NULL, "exit: too many arguments",
					EXIT_FAILURE));
	else if (!(ft_atoi_safe(argv[1], &exit_status)))
		return (investigate_error(1, NULL, "exit: numeric argument required",
					EXIT_FAILURE));
	else
	{
		history_write_to_histfile();
		conf_term_canonical();
		exit(exit_status);
	}
	return (EXIT_SUCCESS);
}
