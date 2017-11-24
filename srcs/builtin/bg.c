#include "t_env.h"
#include "libft.h"
#include <unistd.h>
#include "failure.h"
#include "job_control.h"

int		builtin_bg(t_env *env, const char **argv)
{
	t_job_control	*jc;
	t_job			*j;
	int				nbr;

	(void)env;
	j = NULL;
	jc = singleton_jc();
	if (!argv[1])
	{
		if (!(j = ft_genlst_last(jc->first_job)))
			return (investigate_error(1, NULL, "bg: no current job", \
						EXIT_FAILURE));
	}
	else if (argv[1] && !argv[2])
	{
		if (argv[1][0] == '%' && ft_atoi_safe(argv[1] + 1, &nbr))
			j = ft_genlst_get_n(jc->first_job, nbr > 0 ? nbr - 1 : nbr);
	}
	if (!j)
		return (investigate_error(1, NULL, "bg: no such job", EXIT_FAILURE));
	continue_job(j, 0);
	return (EXIT_SUCCESS);
}
