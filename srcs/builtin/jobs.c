#include "t_env.h"
#include "libft.h"
#include <unistd.h>
#include "failure.h"
#include "job_control.h"

static void		print_command(t_job *j)
{
	t_process	*p;
	p = j->first_process;
	while (p)
	{
		fprintf(stderr, "%s %s", p->av, p->next ? "| " : "");
		p = p->next;
	}
}

static void		print_status(t_job *j)
{
	if (job_is_stopped (j))
		fprintf(stderr, "suspended ");
	else
		fprintf(stderr, "running   ");
}

int		builtin_jobs(t_env *env, const char **argv)
{
	t_job_control	*jc;
	t_job		*j;
	int			i;

	(void)env;
	(void)argv;
	i = 1;
	jc = singleton_jc();
	j = jc->first_job;	
	while (j)
	{
		fprintf(stderr, "[%d]    ", i);
		print_status(j);
		print_command(j);
		ft_putchar('\n');
		j = j->next;
		i++;
	}
	return (EXIT_SUCCESS);
}
