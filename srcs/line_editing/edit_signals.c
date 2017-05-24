#include "completion.h"
#include "line_editing.h"

void	edit_handle_singwinch(int signum)
{
	//put_termcap("cr");
	//put_termcap("cd");
	//comple_clear(*singleton_comple());
	singleton_comple()->ws_col = get_ws_col();
	//edit_clear(*singleton_comple());
	//put_termcap("cl");
	edit_refresh(singleton_line());
	(void)signum;
}

void	edit_set_signals(void)
{
	signal(SIGWINCH, edit_handle_singwinch);
}
