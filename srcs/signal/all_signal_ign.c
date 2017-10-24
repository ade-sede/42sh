#include "my_signal.h"

void		all_signal_ign(void)
{
	int		x;

	x = 0;
	while (x < 31)
	{
		if (x != SIGINT && x != SIGSTOP && x != SIGCHLD && x != SIGWINCH)
			signal(x, SIG_IGN);
		x++;
	}
}
