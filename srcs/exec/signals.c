#include "env.h"
#include <signal.h>

t_env	*singleton_env()
{
	static t_env	env;

	return (&env);
}

void	handle_sigint(int signum)
{
	kill(singleton_env()->child_pid, signum);
}

void	set_signals()
{
	signal(SIGINT, handle_sigint);
}
