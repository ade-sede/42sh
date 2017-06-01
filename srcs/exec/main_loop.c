#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"


void	exec(t_env *env, const char **argv)
{
	if (!(exec_builtin(env, argv)))
		fork_exec_bin(env, argv);
}

void	main_loop(t_env *env)
{
	char		**argv;
/* # define NO_TERMCAPS */
	char		*buf;

	singleton_line()->len = 0;
	singleton_line()->pos = 0;
	singleton_line()->visu_mode = 0;
	singleton_line()->copied_text = NULL;
	singleton_line()->ws_col = get_ws_col();
	singleton_line()->buff = ft_strnew(4096);
	while (42)
	{
		//refresh_buff_and_history();
		//line = get_input(env);
#ifdef NO_TERMCAPS
# define LOCAL_BUFF_SIZE 4096
# define buf no_term_buff
		char	no_term_buff[LOCAL_BUFF_SIZE];
		ft_bzero(buf, LOCAL_BUFF_SIZE);
		read(0, buf, LOCAL_BUFF_SIZE);
		*ft_strchr(buf, '\n') = '\0';
# else
		singleton_line()->prompt_len = put_prompt(env);
		history_init(singleton_hist());
		edit_line_init(singleton_line());
		buf = edit_get_input(env);
#endif
		argv = ft_strsplit_quotes(buf, " \t");
		exec_expand_args(*env, argv);
		set_signals();
		exec(env, (const char **)argv);
		ft_arraydel(&argv);
	}
#ifdef buf
# undef buf
#endif
}

/*
void		exit_proper(int signum)
{
	conf_term_out();
	(void)signum;
	exit(1);
}

void	set_signals(void)
{
	signal(SIGHUP, exit_proper);
	//signal(SIGWINCH, refresh_screen);
	//signal(SIGCONT, restart);
	//signal(SIGTSTP, suspend);
	signal(SIGINT, exit_proper);
	signal(SIGTERM, exit_proper);
	signal(SIGQUIT, exit_proper);
	signal(SIGFPE, exit_proper);
	signal(SIGKILL, exit_proper);
}*/
