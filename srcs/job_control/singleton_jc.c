#include "job_control.h"

t_job_control	*singleton_jc(void)
{
	static	t_job_control jc;

	return (&jc);
}
