int		builtin_jobs(t_env *env, const char **argv)
{
	t_job_control	*jc;
	t_job	*j;
	int		i;

	i = 1;
	jc = singleton_jc();
	j = jc->first_job;	
	while (j)
	{
		printf("[%d]   %s %s", i, 
		j = j->next;
		i++;
	}
}
