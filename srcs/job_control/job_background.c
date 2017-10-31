#include "job_control.h"

void	put_job_in_background(t_job *j, int cont)
{
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
}
