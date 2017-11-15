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
	char	*buff;
	int		fd;
	char	*tmp;

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
	if (!(buff = stream_get_line(fd)))
		return ;
	lex_and_parse(NULL, buff, modes);
	free(buff);
}

int		main(int ac, char **av)
{
	extern const char	**environ;
	t_env				*env;
	t_job_control		*jc;
	t_modes				modes;

	ft_bzero(&modes, sizeof(t_modes));
	read_args(ac, av, &modes);
	jc = singleton_jc();
	env = singleton_env();
	env_load_base_env(env, environ);
	if (modes.mode == 0)
		init_job_control(jc);
	if (!jc->shell_is_interactive)
	{
		modes.mode = FILE_MODE;
		modes.stream = STDIN_FILENO;
	}
	if (modes.mode == INTERACTIVE_MODE)
	{
		conf_term_in();
		history_load(singleton_hist(), env);
		create_ternary_tree(env);
	}
	local_add_change_from_key_value(&env->local, "$?", "0");
	read_pointrc(env);
	main_loop(env, &modes);
	env_free_env(env);
	return (0);
}
		//exit(ft_atoi(local_get_value(singleton_env()->local, "$?")));
