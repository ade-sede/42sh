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


#include "failure.h"
#include <stdio.h>
#include <errno.h>

int	main(void)
{
	extern const char	**environ;
	t_env				*env;

	all_signal_ign();
	env = singleton_env();
	env_load_base_env(env, environ);
	create_ternary_tree(env);
	history_load(singleton_hist(), env);
	conf_term_in();
	main_loop(env);
	env_free_env(env);
	return (0);
}
