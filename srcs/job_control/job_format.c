#include "job_control.h"
#include <stdio.h>

int		job_number(t_job *j)
{
	t_job	*first_job;
	int		i;

	i = 1;
	first_job = singleton_jc()->first_job;
	while (first_job && first_job != j)
	{
		i++;
		first_job = first_job->next;
	}
	return (i);
}

void	format_job_info_process(t_job *j, const char *status)
{
	t_process	*p;
	char		*job_no;
	size_t		job_no_length;

	job_no = ft_itoa(job_number(j));
	job_no_length = ft_strlen(job_no);
	fprintf(stderr, "[%d]", job_number(j));
	p = j->first_process;
	fprintf(stderr, " %ld %s: %s%s\n ", (long)p->pid, status, p->av, p->next ? " |" : "");
	p = p->next;
	while (p)
	{
		ft_putnstr("                ", job_no_length + 2);
		fprintf(stderr, "%ld %s: %s%s\n ", (long)p->pid, status, p->av, p->next ? " |" : "");
		p = p->next;
	}
}
