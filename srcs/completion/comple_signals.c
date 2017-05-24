#include "completion.h"
#include "line_editing.h"

void	comple_handle_singwinch(int signum)
{
	//put_termcap("cr");
	//put_termcap("cd");
	//comple_clear(*singleton_comple());
	comple_init_winch(singleton_comple());
	comple_clear(*singleton_comple());
	put_termcap("cl");
	comple_refresh(singleton_line(), *singleton_comple());
	(void)signum;
}

void	comple_set_signals(void)
{
	signal(SIGWINCH, comple_handle_singwinch);
}
