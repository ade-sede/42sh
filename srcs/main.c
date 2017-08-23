#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"
#include "history.h"
#include "completion.h"

int	main(void)
{
	printf("%d\n", getpid());
	extern const char	**environ;

	env_load_base_env(singleton_env(), environ);
	test_ternary_tree();
#ifndef NO_TERMCAPS
	history_load(singleton_hist(), singleton_env());
	conf_term_in();
#endif
	main_loop(singleton_env());
	env_free_env(singleton_env());
	return (0);
}
