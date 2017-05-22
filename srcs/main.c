#include "env.h"
#include "exec.h"
#include "libft.h"
#include "printf.h"
#include "line_editing.h"

int	main(void)
{
	t_env			env;
	extern const char	**environ;

	env_load_base_env(&env, environ);
	conf_term_in();
	main_loop(&env);
	return (0);
}


