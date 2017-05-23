#include "completion.h"
#include "line_editing.h"

void	comple_handle_singwinch(int signum)
{
	//put_termcap("cr");
	//put_termcap("cd");
	put_termcap("cl");
	//comple_clear(*singleton_comple());
	comple_init_winch(singleton_comple());
	comple_refresh(line(), *singleton_comple());
	(void)signum;
}

void	comple_set_signals(void)
{
	signal(SIGWINCH, comple_handle_singwinch);
}
