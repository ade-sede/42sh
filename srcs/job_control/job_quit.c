
void	quit_job(int signum)
{
	kill(-pid, SIGINT); 
}

signal(SIGINT, quit_job);
