#include "env.h"
#include "libft.h"
#include <unistd.h>
#include "failure.h"
#include "job_control.h"

int		builtin_bg(t_env *env, const char **argv)
{
	t_job_control	*jc;
	t_job			*j;

	(void)env;
	(void)argv;
	jc = singleton_jc();
	if(!(j = ft_genlst_last(jc->first_job)))
		return (investigate_error(1, NULL, "bg: no current job", EXIT_FAILURE));
	continue_job(j, 0);
	return (EXIT_SUCCESS);
}
