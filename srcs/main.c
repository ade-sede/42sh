#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"

int	main(void)
{
	extern const char	**environ;

	env_load_base_env(singleton_env(), environ);
# define NO_TERMCAPS
#ifndef NO_TERMCAPS
	conf_term_in();
#endif
	history_load(singleton_hist(), singleton_env());
	main_loop(singleton_env());
	env_free_env(singleton_env());
	return (0);
}


