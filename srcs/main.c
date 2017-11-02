#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"
#include "completion.h"
#include "get_next_line.h"
#include "color.h"
#include "my_signal.h"
#include "job_control.h"

#include "failure.h"
#include <stdio.h>
#include <errno.h>

void	read_args(int ac, char **av, int *stream, char **buf, int *c_opt)
{
	if (ac == 1)
		return ;
	else if (ac == 2)
	{
		if ((*stream = open(av[1], O_RDONLY)) == -1)
		{
			perror("");
			exit(1);
		}
		return ;
	}
	else if (ac == 3 && ft_strequ(av[1], "-c"))
	{
		*c_opt = 1;
		*buf = av[2];
	}
	else
	{
		dprintf(2, "Usage: 42sh [script_file]\n");
		dprintf(2, "Usage: 42sh [-c string]\n");
		exit(1);
	}
}

int		main(int ac, char **av)
{
	extern const char	**environ;
	t_env				*env;
	t_job_control		*jc;
	char				*buff_c_opt = NULL;
	int					stream = 0;
	int					c_opt = 0;

	read_args(ac, av, &stream, &buff_c_opt, &c_opt);
	jc = singleton_jc();
	env = singleton_env();
	env_load_base_env(env, environ);
	if (stream == 0 && !c_opt)
		init_job_control(jc);
	if (jc->shell_is_interactive)
		conf_term_in();
	create_ternary_tree(env);
	history_load(singleton_hist(), env);
	main_loop(env, stream, buff_c_opt, c_opt);
	env_free_env(env);
	return (0);
}
