#include "job_control.h"

int		put_job_in_background(t_job *j, int cont)
{
	format_job_info_process(j, "launched");
	if(cont)
		if(kill(-j->pgid, SIGCONT) < 0)
			perror("kill(SIGCONT)");
	return (EXIT_SUCCESS);
}
