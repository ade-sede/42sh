#include <stdio.h>
#include "environ.h"
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "exec.h"
#include "local.h"
#include <pwd.h>
#include "modes.h"

void	read_args(int ac, char **av, t_modes *modes)
{
	if (ac == 1)
		return ;
	else if (ac == 2)
	{
		if ((modes->stream = open(av[1], O_RDONLY)) == -1)
		{
			perror("");
			exit(1);
		}
		modes->mode = FILE_MODE;
		return ;
	}
	else if (ac == 3 && ft_strequ(av[1], "-c"))
	{
		modes->mode = STRING_MODE;
		modes->string = av[2];
		//printf("modes->string %s\n", modes->string);
	}
	else
	{
		dprintf(2, "Usage: 42sh [script_file]\n");
		dprintf(2, "Usage: 42sh [-c string]\n");
		exit(1);
	}
}

#include <stdio.h>
void	read_pointrc(t_env *env)
{
	int		fd;
	char	*tmp;
	t_modes				modes;

	ft_bzero(&modes, sizeof(t_modes));
	tmp = ft_gethome();
	/* CHECK THIS */
	if (tmp)
		tmp = ft_strjoin(tmp, "/.42shrc");
	else
		return ;
	(void)env;

	if ((fd = open(tmp, O_RDONLY)) == -1)
	{
		free(tmp);
		perror("");
		return ;
	}
	free(tmp);
	modes.mode = FILE_MODE; 
	modes.stream = fd;
	main_loop(env, &modes);
}

#include <sys/resource.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	extern const char	**environ;
	t_env				*env;
	t_job_control		*jc;
	t_modes				modes;

	ft_bzero(&modes, sizeof(t_modes));
	read_args(ac, av, &modes);
	env = singleton_env();
	env_load_base_env(env, environ);
	jc = singleton_jc();
	read_pointrc(env);
	if (modes.mode == 0)
		init_job_control(jc);
	if (!jc->shell_is_interactive && modes.mode == 0)
	{
		modes.mode = FILE_MODE;
		modes.stream = STDIN_FILENO;
	}
	if (modes.mode == INTERACTIVE_MODE)
	{
		conf_term_init();
		history_load(singleton_hist(), env);
		create_ternary_tree(env);
	}
	local_add_change_from_key_value(&env->local, "?", "0");
	if (!(main_loop(env, &modes)))
		exit(ft_atoi(local_get_value(singleton_env()->local, "?")));
	env_free_env(env);
	return (0);
}
