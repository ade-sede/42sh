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

int	main(void)
{
	extern const char	**environ;
	t_env				*env;
	t_job_control		*jc;

	/* jc.first_job = NULL; */
	jc = singleton_jc();
	env = singleton_env();
	env_load_base_env(env, environ);
	init_shell(jc);
	if (jc->shell_is_interactive)
		conf_term_in();
	create_ternary_tree(env);
	history_load(singleton_hist(), env);
	main_loop(env);
	env_free_env(env);
	return (0);
}
